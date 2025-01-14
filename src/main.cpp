#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <chrono>
#include <assert.h>
#include <unistd.h>
#include "./util/IO.hpp"
#include "./util/cw.hpp"
#include "./util/update.hpp"
#include "./util/segTree.hpp"
#include "./util/util.hpp"
#include "./util/stopwordsFilter.hpp"
#include "./heapGroup/HeapGroup.hpp"
#include <omp.h>
using namespace std;

ofstream ofs;

int doc_length = 0;
int k = 64;
int min_seq_len;
unsigned int slide_len = 128;
unsigned int win_stride = 64;
double threshold = 0;
int queryNum = 0; // set a default number
string src_file;
string index_file;
const int tokenNum = 50257;
const double eps = 1e-10;

double group_cost[128] = {0};

const string stpwords_path = "path/to/your/stopwords_tokens.bin";
StopwordsFilter filter(stpwords_path);

void getQuerySeqs(vector<vector<int>> &querySeqs, string query_bin_file)
{
    loadBin(query_bin_file, querySeqs);
}

// Function to compute the signature of a sequence defined by a range [begin, end).
// begin: Iterator to the beginning of the range.
// end: Iterator to the end of the range.
// signature: The output vector where the signature will be stored.
// hf: The vector of hash functions, represented as pairs of integers.
template <typename Iterator>
void getSignature(Iterator &begin, Iterator &end, vector<int> &signature)
{
    for (int hid = 0; hid < k; hid++)
    {
        unsigned int tmp_min = numeric_limits<int>::max();
        for (auto it = begin; it != end; ++it)
        {
            int v = filter.filtered_hash(*it, hid);
            if (v < tmp_min)
            {
                tmp_min = v;
                signature[hid] = *it;
            }
        }
    }
}

// Function to compute signatures for sliding windows in a set of sequences.
// seqs: The input sequences.
// signatures: The output vector of signatures for each window.
// hf: The vector of hash functions.
// win_len: The length of the sliding window.
void slideWinAndGetSig(vector<vector<int>> &seqs, vector<vector<int>> &signatures, vector<pair<unsigned int, unsigned int>> &win_pos, unsigned int win_len, unsigned int stride)
{
    unsigned int total_win_num = 0;
    for (auto &seq : seqs)
    {
        if (seq.size() < win_len)
            continue;
        total_win_num += (seq.size() - win_len) / stride + 1;
    }
    cout << total_win_num << endl;
    signatures = vector<vector<int>>(total_win_num, vector<int>(k));
    win_pos.resize(total_win_num);
    total_win_num = 0;

    unsigned int seq_cnt = 0;
    for (auto &seq : seqs)
    {
        seq_cnt++;
        if (seq.size() < win_len)
            continue;
        int tmp_cnt = 0;
        for (size_t i = 0; i < seq.size(); i += stride)
        {
            if (i + win_len > seq.size())
                break;
            auto begin = seq.begin() + i;
            auto end = begin + win_len;
            if (filter.countNonStopwords(begin, end) >= min_seq_len)
            { // if there are too little nonstopwords
                getSignature(begin, end, signatures[total_win_num]);
                // for(auto & toekn_withMinHash: signatures[total_win_num]){
                //     cout<< toekn_withMinHash<<" ";
                // }cout<<endl;
            }
            else
            {
                printf("It is cleared of this %d %d\n", seq_cnt - 1, tmp_cnt);
                signatures[total_win_num].clear(); // clear this signature means it do not need to query
            }

            win_pos[total_win_num++] = make_pair(seq_cnt - 1, tmp_cnt++);
        }
    }
}

void getSignatures(vector<vector<int>> &seqs, vector<vector<int>> &signatures)
{
    for (int did = 0; did < seqs.size(); did++)
    {
        vector<int> minimal(k, numeric_limits<int>::max());
        for (int hid = 0; hid < k; hid++)
        {
            for (int i = 0; i < seqs[did].size(); i++)
            {
                int v = filter.filtered_hash(hid, seqs[did][i]);
                if (v < minimal[hid])
                {
                    minimal[hid] = v;
                    signatures[did][hid] = seqs[did][i];
                }
            }
        }
    }
}

bool lineSweep(vector<CW> &cws, unsigned int cw_thres)
{
    vector<pair<unsigned int, int>> updates;
    for (auto cw : cws)
    {
        updates.emplace_back(cw.l, 1);
        updates.emplace_back(cw.r + 1, -1);
    }
    sort(updates.begin(), updates.end());
    int cnt = 0;
    for (int i = 0; i < updates.size(); i++)
    {
        auto &update = updates[i];
        cnt += update.second;
        if (cnt >= cw_thres)
        {
            return true;
        }
    }
    return false;
}

void groupbyTid(unordered_map<int, vector<CW>> &tidToCW, const vector<int> &signature, vector<vector<vector<CW>>> &cws)
{   
    auto tid = omp_get_thread_num();
    auto st = timerStart();

    HeapGroup heapGroup;
    heapGroup.init(cws, signature, threshold);
    heapGroup.run(tidToCW);
    group_cost[tid] += timerCheck(st);
    
}

void InnerScan(vector<CW> &cws, unordered_set<int> &ids, double threshold, vector<pair<int, int>> &Rranges)
{
    vector<Update> updates;
    for (auto id : ids)
    {
        updates.emplace_back(cws[id].c, 0, 0, id, 1);
        updates.emplace_back(cws[id].r + 1, 0, 0, id, -1);
    }
    int cnt = 0;
    sort(updates.begin(), updates.end());
    for (int i = 0; i < updates.size(); i++)
    {
        Update &update = updates[i];
        if (i > 0 && updates[i].t != updates[i - 1].t)
        {
            if (cnt > k * threshold - eps)
            {
                Rranges.emplace_back(make_pair(updates[i - 1].t, updates[i].t - 1));
            }
        }
        cnt += update.value;
    }
}

void nearDupSearch(unordered_map<int, vector<CW>> &tidToCW, double threshold, unordered_map<int, vector<tuple<int, int, int, int>>> &results, pair<int, int> query_info)
{
    for (auto item : tidToCW)
    {
        auto time_st = timerStart(); //
        int tid = item.first;
        vector<CW> &cws = item.second;
        vector<Update> updates;
        for (int i = 0; i < cws.size(); i++)
        {
            CW &cw = cws[i];
            updates.emplace_back(cw.l, 0, 0, i, 1);
            updates.emplace_back(cw.c + 1, 0, 0, i, -1); // cw.type == cw.id
        }
        sort(updates.begin(), updates.end());

        unordered_set<int> ids;
        for (int i = 0; i < updates.size(); i++)
        {
            Update &update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t)
            {
                if (ids.size() > k * threshold - eps)
                {
                    // cout<<"Enter Here"<<" tid" <<endl;
                    vector<pair<int, int>> Rranges;
                    InnerScan(cws, ids, threshold, Rranges);
                    for (auto Rrange : Rranges)
                    {
                        results[tid].emplace_back(make_tuple(updates[i - 1].t, updates[i].t - 1, Rrange.first, Rrange.second));
                    }
                }
            }
            if (update.value == 1)
            {
                ids.insert(update.type);
            }
            else
            {
                ids.erase(update.type);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "f:i:k:l:t:q:")) != EOF)
    {
        switch (opt)
        {
        case 'f':
            src_file = optarg;
            break;
        case 'i':
            index_file = optarg;
            break;
        case 'k':
            k = atoi(optarg);
            break;
        case 'l':
            doc_length = stoi(optarg);
            break;
        case 't':
            threshold = stof(optarg);
            break;
        case 'q':
            queryNum = stoi(optarg);
            break;
        case '?':
            cout << optarg << endl;
            cout << opterr << endl;
            cout << "Usage: program -f bin_file_path -k k [-l doc_length] -t threshold -q query_num" << endl;
            break;
        }
    }
    cout << "Parameters Summary: " << endl;
    cout << "bin_file_path  : " << src_file << endl;
    cout << "k              : " << k << endl;
    cout << "doc_length     : " << doc_length << endl;
    cout << "threshold      : " << threshold << endl;
    cout << "query_num      : " << queryNum << endl;
    cout << "------------------------------" << endl;

    cout << src_file.substr(src_file.rfind('/') + 1, src_file.rfind('.') - src_file.rfind('/') - 1) << endl;
    char out_file[100];
    sprintf(out_file, "./KMINS_INTERVAL_SCAN_filter_%s_l%d_k%d_t%.1lf_q%d.txt", src_file.substr(src_file.rfind('/') + 1, src_file.rfind('.') - src_file.rfind('/') - 1).c_str(), doc_length, k, threshold, queryNum);
    ofs.open(out_file, std::ofstream::out);

    // stopwordsFilter laod hasher
    filter.load_hasher(k);
    filter.if_filter = true;
    min_seq_len = k / 4;
    // load index
    auto load_st = timerStart();
    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum + 1)); // cws[partition][token][]
    loadCW(index_file, cws);
    cout << "CW Loading Time: " << timerCheck(load_st) << endl;

    // Prepare Query Sequences
    auto query_prep = timerStart();
    vector<vector<int>> querySeqs;
    getQuerySeqs(querySeqs, src_file);
    // shrink the query
    if(queryNum != 0 && queryNum < querySeqs.size())
        querySeqs.resize(queryNum);
    vector<vector<int>> signatures;
    vector<pair<unsigned int, unsigned int>> sig_info;
    slideWinAndGetSig(querySeqs, signatures, sig_info, slide_len, win_stride);
    cout << "Hashing Query: " << timerCheck(query_prep) << endl;

    double total_cost = 0;
    cout << "Strart: finding signatures" << endl;

    auto query_st = timerStart();

#pragma omp parallel for
    for (int i = 0; i < signatures.size(); i++)
    {
        if (signatures[i].size() == 0)
            continue;

        auto query_one_st = timerStart();
        unordered_map<int, vector<CW>> tidToCW;
        groupbyTid(tidToCW, signatures[i], cws);
        unordered_map<int, vector<tuple<int, int, int, int>>> results;
        nearDupSearch(tidToCW, threshold, results, sig_info[i]);
        ofs << i << " : " << tidToCW.size() << " cost:" << timerCheck(query_one_st) << endl;
        if (results.size() != 0)
        {
            auto query_info = sig_info[i];
            cout << query_info.first << " " << query_info.second << " match : [";
            for (auto &pair : results)
            {
                cout << pair.first << ",";
            }
            cout << "]\n";
        }
    }

    total_cost = timerCheck(query_st);
    cout << "Traversing " << signatures.size() << ": " << total_cost << endl;
    cout << "Grouping cost: " << averageNonZero(group_cost, 128)<<endl;
    ofs.close();
    return 0;
}