#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <unordered_map>
#include <map>
#include <chrono>
#include <assert.h>
#include <unistd.h>
#include "../IO.hpp"
#include "../cw.hpp"
#include "../update.hpp"
#include "../segTree.hpp"

using namespace std;

ofstream ofs;

int doc_num;
int doc_length = 0;
int INTERVAL_LIMIT = 0;
int k = 64;
double threshold = 0;
int queryNum = 0;
string src_file;

const int tokenNum = 50257;
const int p = 998244353;
const double eps = 1e-10;
const int m = p / k * k;

// mt19937 mt_rand(time(0));
mt19937 mt_rand(0);

std::chrono::_V2::system_clock::time_point timer;

void timerStart()
{
    timer = chrono::high_resolution_clock::now();
}

double timerCheck()
{
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - timer);
    return duration.count() / 1000000.0;
}

vector<pair<int, int>> generateHF()
{
    vector<pair<int, int>> HF;
    for (int i = 0; i < k; i++)
    {
        HF.emplace_back(mt_rand() % p, mt_rand() % p);
    }
    return HF;
}

int eval(pair<int, int> hf, int x)
{
    return (1LL * x * hf.first + hf.second) % p % m;
}

void partition(int doc_id, vector<int> &doc, vector<pair<int, int>> &seg, const int& n, int l, int r, vector<vector<CW>> &cws)
{
    if (l + INTERVAL_LIMIT > r)
        return;
    pair<int, int> ret(numeric_limits<int>::max(), -1);
    int a = l, b = r;
    for (a += n, b += n; a <= b; ++a /= 2, --b /= 2)
    {
        if (a % 2 == 1)
            if (seg[a].first < ret.first)
                ret = seg[a];
        if (b % 2 == 0)
            if (seg[b].first < ret.first)
                ret = seg[b];
    }

    cws[doc[ret.second]].emplace_back(doc_id, l, ret.second, r);
    partition(doc_id, doc, seg, n, l, ret.second - 1, cws);
    partition(doc_id, doc, seg, n, ret.second + 1, r, cws);
}

void buildCW(vector<vector<int>> &docs, vector<vector<vector<CW>>> &cws, const vector<pair<int, int>> &hf)
{
    int maxlength = 0;
    for (auto doc: docs) {
        maxlength = max(maxlength, int(doc.size()));
    }
    vector<vector<int>> pos(k);
    vector<pair<int, int>> seg(maxlength * 2);
    vector<int> hval(maxlength);

    for (int doc_id = 0; doc_id < docs.size(); doc_id++)
    {
        vector<int> &doc = docs[doc_id];

        int n = doc.size();

        for (int hid = 0; hid < k; hid++)
        {
            for (int i = 0; i < doc.size(); i++)
            {
                hval[i] = eval(hf[hid], doc[i]);
            }

            // build segment tree
            for (int i = 0; i < n; i++)
            {
                seg[n + i].first = hval[i];
                seg[n + i].second = i;
            }
            for (int i = n - 1; i; i--)
            {
                if (seg[2 * i].first < seg[2 * i + 1].first)
                    seg[i] = seg[2 * i];
                else
                    seg[i] = seg[2 * i + 1];
            }
            partition(doc_id, doc, seg, n, 0, n - 1, cws[hid]);
            
        }
    }
}

void statistics(vector<vector<vector<CW>>> &cws)
{
    long long total_cws_amount = 0;
    long long nonempty_amount = 0;
    for (int pid = 0; pid < k; pid++)
    {
        for (int tid = 0; tid < tokenNum; tid++)
        {
            nonempty_amount += cws[pid][tid].size();
        }
    }
    total_cws_amount = nonempty_amount;
    cout << "cws amount: " << total_cws_amount << endl;
    ofs << total_cws_amount << endl;
}

void sortCW(vector<vector<vector<CW>>> &cws)
{
    for (int pid = 0; pid < k; pid++)
    {
        for (int tid = 0; tid <= tokenNum; tid++)
        {
            sort(cws[pid][tid].begin(), cws[pid][tid].end());
        }
    }
}

void getQuerySeqs(vector<vector<int>> &querySeqs) {
    loadSamples(src_file, querySeqs, doc_num, queryNum);
}

void getSignatures(vector<vector<int>> &seqs, vector<vector<int>> &signatures, const vector<pair<int, int>> &hf)
{
    for (int did = 0; did < queryNum; did++) {
        vector<int> minimal(k, numeric_limits<int>::max());
        for (int hid = 0; hid < k; hid++)
        {
            for (int i = 0; i < seqs[did].size(); i++)
            {
                int v = eval(hf[hid], seqs[did][i]);
                if (v < minimal[hid])
                {
                    minimal[hid] = v;
                    signatures[did][hid] = seqs[did][i];
                }
            }
        }
    }
}

void groupbyTid(unordered_map<int, vector<CW>> &tidToCW, vector<int> &signature, vector<vector<vector<CW>>> &cws)
{
    for (int pid = 0; pid < k; pid++)
    {
        for (auto cw : cws[pid][signature[pid]])
        {
            // Here maybe we can first record how many elements should be used first and then put them together.
            tidToCW[cw.T].emplace_back(cw);
        }
    }
}

void generateUpdates(unordered_map<int, vector<CW>> &tidToCW, unordered_map<int, vector<Update>> &tidToUpdates)
{
    for (auto item : tidToCW)
    {
        int tid = item.first;
        vector<CW> &cws = item.second;
        for (auto cw : cws)
        {
            if (cw.c == -1)
            {
                tidToUpdates[tid].emplace_back(cw.l, cw.l, cw.r, 0, 1);
                tidToUpdates[tid].emplace_back(cw.r + 1, cw.l, cw.r, 0, -1);
            }
            else
            {
                tidToUpdates[tid].emplace_back(cw.l, cw.c, cw.r, 1, 1);
                tidToUpdates[tid].emplace_back(cw.c + 1, cw.c, cw.r, 1, -1);
            }
        }
        sort(tidToUpdates[tid].begin(), tidToUpdates[tid].end());
    }
}

void nearDupSearch(vector<vector<int>> &docs, unordered_map<int, vector<Update>> &tidToUpdates, double threshold, unordered_map<int, vector<tuple<int, int, int, int>>> &results)
{
    SegmentTree segtree;
    ofs << tidToUpdates.size() << endl; //
    for (auto item : tidToUpdates)
    {
        timerStart(); //
        int tid = item.first;
        vector<Update> &updates = item.second;
        ofs << updates.size() / 2 << endl; //

        map<int, int> discret;
        vector<int> rev;
        rev.emplace_back(0);
        for (auto update : updates)
        {
            discret.insert(make_pair(update.l, 0));
            discret.insert(make_pair(update.r, 0));
        }
        int cnt = 0;
        for (auto &it : discret)
        {
            it.second = ++cnt;
            rev.emplace_back(it.first);
        }

        segtree.init(cnt);
        segtree.build(1, 1, cnt);

        for (int i = 0; i < updates.size(); i++)
        {
            Update update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t)
            {
                vector<pair<int, int>> Rranges;
                segtree.query(1, 1, cnt, k * threshold - eps, Rranges);
                for (auto Rrange : Rranges)
                {
                    results[tid].emplace_back(make_tuple(updates[i - 1].t, updates[i].t - 1, rev[Rrange.first], rev[Rrange.second]));
                }
                // printf("%d\n", Rranges.size());
            }
            if (update.type == 0)
            {
                segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value * threshold);
            }
            else
            {
                segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value);
            }

            if (i == updates.size() - 1)
            {
                vector<pair<int, int>> Rranges;
                segtree.query(1, 1, cnt, k * threshold - eps, Rranges);
                for (auto Rrange : Rranges)
                {
                    results[tid].emplace_back(make_tuple(updates[i].t, docs[tid].size(), rev[Rrange.first], rev[Rrange.second]));
                }
                // printf("%d\n", Rranges.size());
            }
        }
        ofs << results[tid].size() << endl; //
        ofs << timerCheck() << endl; //
    }
}

void statistics(unordered_map<int, vector<CW>> &tidToCW, unordered_map<int, vector<tuple<int, int, int, int>>> &results)
{
    int collided_cws_amount = 0;
    for (auto cws: tidToCW) {
        ofs << cws.second.size() << " ";
        collided_cws_amount += cws.second.size();
    }
    // cout << "collided cws amount: " << collided_cws_amount << endl;
    // cout << "results text amount: " << results.size() << endl;
    int results_cws_amount = 0;
    for (auto result: results) {
        results_cws_amount += result.second.size();
        // cout << "tid: " << result.first << endl;
        // for (auto tu: result.second) {
        //     cout << "[" << get<0>(tu) << ", " << get<1>(tu) << "] * [" << get<2>(tu) << ", " << get<3>(tu) << "]" << endl;
        // }
    }
    // cout << "results cws amount: " << results_cws_amount << endl;
}

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "f:n:k:l:t:q:")) != EOF) {
        switch (opt) {
            case 'f':
                src_file = optarg;
                break;
            case 'n':
                doc_num = stoi(optarg);
                break;
            case 'k':
                k = atoi(optarg);
                break;
            case 'l':
                doc_length = stoi(optarg);
                break;
            case 'L':
                INTERVAL_LIMIT = stoi(optarg);
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
                cout << "Usage: program -f bin_file_path -n doc_num -k k [-l doc_length] [-L interval_limit] -t threshold -q query_num" << endl;
                break;
        }
    }
    cout << "Parameters Summary: " << endl;
    cout << "bin_file_path  : " << src_file << endl;
    cout << "doc_num        : " << doc_num << endl;
    cout << "k              : " << k << endl;
    cout << "doc_length     : " << doc_length << endl;
    cout << "interval_limit : " << INTERVAL_LIMIT << endl;
    cout << "threshold      : " << threshold << endl;
    cout << "query_num      : " << queryNum << endl;
    cout << "------------------------------" << endl;


    cout << src_file.substr(src_file.rfind('/') + 1, src_file.rfind('.') - src_file.rfind('/') - 1) << endl;
    char out_file[100];
    sprintf(out_file, "ExpResults/KMINS_%s_n%d_l%d_k%d_t%.1lf_q%d.txt", src_file.substr(src_file.rfind('/') + 1, src_file.rfind('.') - src_file.rfind('/') - 1).c_str(), doc_num, doc_length ,k, threshold, queryNum);
    ofs.open(out_file, std::ofstream::out);

    // Load documents
    timerStart();
    vector<vector<int>> docs;
    if (doc_length == 0)
        loadBin(src_file, docs, doc_num);
    else
        loadBin(src_file, docs, doc_num, doc_length);
    cout << "Load Time: " << timerCheck() << endl;

    // Generate Comapct Windows
    timerStart();
    vector<pair<int, int>> hf = generateHF();
    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum + 1)); //cws[partition][token][]
    buildCW(docs, cws, hf);
    cout << "CW Generation Time: " << timerCheck() << endl;
    ofs << timerCheck() << endl;

    statistics(cws);

    if (queryNum == 0)
        return 0;
    // Prepare Query Sequences    
    vector<vector<int>> querySeqs, signatures(queryNum, vector<int>(k));
    getQuerySeqs(querySeqs);
    getSignatures(querySeqs, signatures, hf);
    
    // Do Query
    for (int i = 0; i < queryNum; i++) {
        unordered_map<int, vector<CW>> tidToCW;
        groupbyTid(tidToCW, signatures[i], cws);
        unordered_map<int, vector<Update>> tidToUpdates;
        generateUpdates(tidToCW, tidToUpdates);
        unordered_map<int, vector<tuple<int, int, int, int>>> results;
        nearDupSearch(docs, tidToUpdates, threshold, results);
        // statistics(tidToCW, results);
    }
    cout << endl;
    return 0;
}