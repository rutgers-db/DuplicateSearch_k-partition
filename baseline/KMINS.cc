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
#include "../IO.hpp"
#include "../cw.hpp"
#include "../update.hpp"
#include "../segTree.hpp"

using namespace std;

int k = 0;
float threshold = 0;
int queryNum = 0;
string index_file;
string query_file;
string out_file;
ofstream ofs;
int method = 0;

const int tokenNum = 50257;
const int p = 998244353;
const float eps = 1e-6;
int m = 0;

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

int eval(pair<int, int> hf, int x)
{
    return (1LL * x * hf.first + hf.second) % p % m;
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

void getQuerySeqs(vector<vector<int>> &querySeqs) {
    loadBin(query_file, querySeqs, queryNum);
    // loadBin(query_file, querySeqs, queryNum + 100);
    // querySeqs.erase(querySeqs.begin(), querySeqs.begin() + 100);
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
    unordered_map<int, int> cnt;
    for (int pid = 0; pid < k; pid++) {
        for (auto cw : cws[pid][signature[pid]]) {
            cnt[cw.T] += 1;
        }
    }
    for (int pid = 0; pid < k; pid++)
    {
        for (auto cw : cws[pid][signature[pid]])
        {
            // Here maybe we can first record how many elements should be used first and then put them together.
            // if (cnt[cw.T] > k * threshold - eps) {
                tidToCW[cw.T].emplace_back(cw);
            // }
        }
    }
}

void nearDupSearch(unordered_map<int, vector<CW>> &tidToCW, float threshold, unordered_map<int, vector<tuple<int, int, int, int>>> &results)
{
    SegmentTree segtree;
    for (auto item : tidToCW)
    {
        timerStart(); //
        int tid = item.first;
        vector<CW>& cws = item.second;
        vector<Update> updates;
        for (auto cw: cws) {
            updates.emplace_back(cw.l, cw.c, cw.r, 1, 1.0);
            updates.emplace_back(cw.c + 1, cw.c, cw.r, 1, -1.0);
        }
        sort(updates.begin(), updates.end());

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

        float update_cnt = 0;
        for (int i = 0; i < updates.size(); i++)
        {
            Update update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t)
            {   
                if(update_cnt > k * threshold - eps){
                    vector<pair<int, int>> Rranges;
                    segtree.query(1, 1, cnt, k * threshold - eps, Rranges);
                    for (auto Rrange : Rranges)
                    {
                        results[tid].emplace_back(make_tuple(updates[i - 1].t, updates[i].t - 1, rev[Rrange.first], rev[Rrange.second]));
                    }
                }
            }
            
            segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value);
            update_cnt = update_cnt + update.value;
            
        }
        ofs << results[tid].size() << endl; //
        ofs << timerCheck() << endl; //
    }
}

void nearDupSearch_longest(unordered_map<int, vector<CW>> &tidToCW, float threshold, unordered_map<int, vector<tuple<int, int>>> &results)
{
    SegmentTree segtree;
    for (auto item : tidToCW)
    {
        timerStart(); //
        int tid = item.first;
        vector<CW>& cws = item.second;
        vector<Update> updates;
        for (auto cw: cws) {
            updates.emplace_back(cw.l, cw.c, cw.r, 1, 1.0);
            updates.emplace_back(cw.c + 1, cw.c, cw.r, 1, -1.0);
        }
        sort(updates.begin(), updates.end());

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

        float update_cnt = 0;
        for (int i = 0; i < updates.size(); i++)
        {
            Update update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t)
            {   
                if(update_cnt > k * threshold - eps){
                    int Rlongest = -1;
                    segtree.queryLongest(1, 1, cnt, k * threshold - eps, Rlongest);
                    if (Rlongest != -1)
                    {
                        results[tid].emplace_back(make_tuple(updates[i - 1].t, rev[Rlongest]));
                    }
                }
            }
            
            segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value);
            update_cnt = update_cnt + update.value;
            
        }
        ofs << results[tid].size() << endl; //
        ofs << timerCheck() << endl; //
    }
}

void InnerScan(vector<CW> &cws, unordered_set<int> &ids, double threshold, vector<pair<int, int>> &Rranges) {
    vector<Update> updates;
    for (auto id: ids) {
        updates.emplace_back(cws[id].c, 0, 0, id, 1);
        updates.emplace_back(cws[id].r + 1, 0, 0, id, -1);
    }
    sort(updates.begin(), updates.end());
    int cnt = 0;
    for (int i = 0; i < updates.size(); i++) {
        Update& update = updates[i];
        if (i > 0 && updates[i].t != updates[i - 1].t) {
            if (cnt > k * threshold - eps) {
                Rranges.emplace_back(make_pair(updates[i - 1].t, updates[i].t - 1));
            }
        }
        cnt += update.value;
    }
}


void OutterScan(unordered_map<int, vector<CW>> &tidToCW, double threshold, unordered_map<int, vector<tuple<int, int, int, int>>> &results)
{
    SegmentTree segtree;
    for (auto item : tidToCW)
    {
        timerStart(); //
        int tid = item.first;
        vector<CW>& cws = item.second;
        vector<Update> updates;
        for (int i = 0; i < cws.size(); i++) {
            CW& cw = cws[i];
            updates.emplace_back(cw.l, 0, 0, i, 1);
            updates.emplace_back(cw.c + 1, 0, 0, i, -1); //cw.type == cw.id
        }
        sort(updates.begin(), updates.end());

        ofs << updates.size() / 2 << endl; //
        
        unordered_set<int> ids;
        for (int i = 0; i < updates.size(); i++) {
            Update& update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t) {
                if (ids.size() > k * threshold - eps) {
                    vector<pair<int, int>> Rranges;
                    InnerScan(cws, ids, threshold, Rranges);
                    for (auto Rrange: Rranges) {
                        results[tid].emplace_back(make_tuple(updates[i - 1].t, updates[i].t - 1, Rrange.first, Rrange.second));
                    }
                }
            }
            if (update.value == 1) {
                ids.insert(update.type);
            }
            else {
                ids.erase(update.type);
            }
        }
        ofs << results[tid].size() << endl; //
        ofs << timerCheck() << endl; //
    }
}


void InnerScan_longest(vector<CW> &cws, unordered_set<int> &ids, double threshold, int &Rlongest) {
    vector<Update> updates;
    for (auto id: ids) {
        updates.emplace_back(cws[id].r, 0, 0, id, 1);
        updates.emplace_back(cws[id].c - 1, 0, 0, id, -1);
    }
    sort(updates.rbegin(), updates.rend());
    int cnt = 0;
    for (int i = 0; i < updates.size(); i++) {
        Update& update = updates[i];
        if (i > 0 && updates[i].t != updates[i - 1].t) {
            if (cnt > k * threshold - eps) {
                Rlongest = updates[i - 1].t;
                return;
            }
        }
        cnt += update.value;
    }
}

void OutterScan_longest(unordered_map<int, vector<CW>> &tidToCW, double threshold, unordered_map<int, vector<tuple<int, int>>> &results)
{
    SegmentTree segtree;
    for (auto item : tidToCW)
    {
        timerStart(); //
        int tid = item.first;
        vector<CW>& cws = item.second;
        vector<Update> updates;
        for (int i = 0; i < cws.size(); i++) {
            CW& cw = cws[i];
            updates.emplace_back(cw.l, 0, 0, i, 1);
            updates.emplace_back(cw.c + 1, 0, 0, i, -1); //cw.type == cw.id
        }
        sort(updates.begin(), updates.end());

        ofs << updates.size() / 2 << endl; //
        
        unordered_set<int> ids;
        for (int i = 0; i < updates.size(); i++) {
            Update& update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t) {
                if (ids.size() > k * threshold - eps) {
                    int Rlongest = -1;
                    InnerScan_longest(cws, ids, threshold, Rlongest);
                    if (Rlongest != -1) {
                        results[tid].emplace_back(make_tuple(updates[i - 1].t, Rlongest));
                    }
                }
            }
            if (update.value == 1) {
                ids.insert(update.type);
            }
            else {
                ids.erase(update.type);
            }
        }
        ofs << results[tid].size() << endl; //
        ofs << timerCheck() << endl; //
    }
}

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "f:i:t:q:m:o:")) != EOF) {
        switch (opt) {
            case 'f':
                query_file = optarg;
            case 'i':
                index_file = optarg;
                break;
            case 't':
                threshold = stof(optarg);
                break;
            case 'q':
                queryNum = stoi(optarg);
                break;
            case 'm':
                method = stoi(optarg);
                break;
            case 'o':
                out_file = optarg;
                break;
            case '?':
                cout << optarg << endl;
                cout << opterr << endl;
                cout << "Usage: program -f query_file_path -i index_file_path -t threshold -q query_num -m method -o out_file" << endl;
                cout << "Method: 0 Segtree, 1 Interval scan" << endl;
                break;
        }
    }
    ofs.open(out_file, std::ofstream::out);
    if (!ofs) {
        cout << "Error open out file" << endl;
        throw "Error open out file";
    }

    vector<vector<vector<CW>>> cws;
    vector<pair<int, int>> hf;
    timerStart();
    loadCW(index_file, cws, hf);
    k = cws.size();
    m = p / k * k;

    cout << "Parameters Summary: " << endl;
    cout << "bin_file_path  : " << index_file << endl;
    cout << "k              : " << k << endl;
    cout << "threshold      : " << threshold << endl;
    cout << "query_num      : " << queryNum << endl;
    cout << "------------------------------" << endl;

    cout << "Load Time: " << timerCheck() << endl;
    statistics(cws);

    // Prepare Query Sequences    
    vector<vector<int>> querySeqs, signatures(queryNum, vector<int>(k));
    getQuerySeqs(querySeqs);
    getSignatures(querySeqs, signatures, hf);
    
    // Do Query
    int results_amount = 0;
    for (int i = 0; i < queryNum; i++) {
        unordered_map<int, vector<CW>> tidToCW;
        groupbyTid(tidToCW, signatures[i], cws);
        if (method == 0) {
            unordered_map<int, vector<tuple<int, int, int, int>>> results;
            nearDupSearch(tidToCW, threshold, results);
            results_amount += results.size();
        }
        else if (method == 1) {
            unordered_map<int, vector<tuple<int, int, int, int>>> results;
            OutterScan(tidToCW, threshold, results);
            results_amount += results.size();
        }
        else if (method == 2) {
            unordered_map<int, vector<tuple<int, int>>> results;
            nearDupSearch_longest(tidToCW, threshold, results);
            results_amount += results.size();
        }
        else {
            unordered_map<int, vector<tuple<int, int>>> results;
            OutterScan_longest(tidToCW, threshold, results);
            results_amount += results.size();
        }
        
    }
    cout << "results text amount: " << results_amount << endl;
    return 0;
}