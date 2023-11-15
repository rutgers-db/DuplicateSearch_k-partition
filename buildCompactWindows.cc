#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <unordered_map>
#include <map>
#include <chrono>
#include <assert.h>
#include "IO.hpp"
#include "cw.hpp"
#include "update.hpp"
#include "segTree.hpp"

using namespace std;

const int tokenNum = 50257;

const int INTERVAL_LIMIT = 0;
const int p = 998244353;
const int k = 2;
const double eps = 1e-10;
const double threshold = 0.8 - eps;
const int m = p / k * k;

mt19937 mt_rand(time(0));
// mt19937 mt_rand(0);

pair<int, int> generateHF() {
    return make_pair(mt_rand() % p, mt_rand() % p);
}

int eval(pair<int, int> hf, int x) {
    return (1LL * x * hf.first + hf.second) % p % m;
}

void partition(int doc_id, vector<int> &doc, vector<pair<int, int>> &seg, vector<int> &pos, int n, int l, int r, vector<vector<CW>> &cws) {
    if (l + INTERVAL_LIMIT > r)
        return;
    // printf("[%d, %d] out of %d\n", l, r, pos.size());
    pair<int, int> ret(numeric_limits<int>::max(), -1);
    int a = l, b = r;
    for (a += n, b += n; a <= b; ++a /= 2, --b /= 2) {
        if (a % 2 == 1)
            if (seg[a].first < ret.first)
                ret = seg[a];
        if (b % 2 == 0)
            if (seg[b].first < ret.first)
                ret = seg[b];
    }

    a = (l == 0) ? 0 : pos[l - 1] + 1;
    b = (r == pos.size() - 1) ? doc.size() - 1 : pos[r + 1] - 1;
    cws[doc[pos[ret.second]]].emplace_back(doc_id, a, pos[ret.second], b);
    partition(doc_id, doc, seg, pos, n, l, ret.second - 1, cws);
    partition(doc_id, doc, seg, pos, n, ret.second + 1, r, cws);
}

void emptyCW(int doc_id, vector<int> &pos, vector<CW> &ecws, int doc_size) {
    if (pos.size() == 0) {
        ecws.emplace_back(doc_id, 0, -1, doc_size - 1);
        return;
    }
    if (pos[0] > 0) {
        ecws.emplace_back(doc_id, 0, -1, pos[0] - 1);
    }
    for (int i = 1; i < pos.size(); i++) {
        if (pos[i - 1] + 1 <= pos[i] - 1) {
            ecws.emplace_back(doc_id, pos[i - 1] + 1, -1, pos[i] - 1);
        }
    }
    if (pos[pos.size() - 1] < doc_size - 1) {
        ecws.emplace_back(doc_id, pos[pos.size() - 1] + 1, -1, doc_size - 1);
    }
}

void buildCW(vector<vector<int>> &docs, vector<vector<vector<CW>>> &cws, pair<int, int> hf) {
    vector<vector<int>> pos(k);
    vector<pair<int, int>> seg;
    vector<int> hval;
    for (int doc_id = 0; doc_id < docs.size(); doc_id++) {
        vector<int>& doc = docs[doc_id];
        if (hval.size() < doc.size()) {
            hval.resize(doc.size());
        }
        for (int pid = 0; pid < k; pid++) {
            pos[pid].clear();
        }
        for (int i = 0; i < doc.size(); i++) {
            hval[i] = eval(hf, doc[i]);
            pos[hval[i] / (m / k)].push_back(i);
        }

        for (int pid = 0; pid < k; pid++) {
            int n = pos[pid].size();
            if (n > 0) {
                if (seg.size() < 2 * n) {
                    seg.resize(2 * n);
                }
                for (int i = 0; i < n; i++) {
                    seg[n + i].first = hval[pos[pid][i]];
                    seg[n + i].second = i;
                }
                for (int i = n - 1; i; i--) {
                    if (seg[2 * i].first < seg[2 * i + 1].first)
                        seg[i] = seg[2 * i];
                    else
                        seg[i] = seg[2 * i + 1];
                }
                partition(doc_id, doc, seg, pos[pid], n, 0, n - 1, cws[pid]);
            }
            emptyCW(doc_id, pos[pid], cws[pid][tokenNum], doc.size());
        }
    }
    
}


void sortCW(vector<vector<vector<CW>>> &cws) {
    int total_cws_amount = 0;
    for (int pid = 0; pid < k; pid++) {
        // printf("pid: %d\n", pid);
        for (int tid = 0; tid <= tokenNum; tid++) {
            sort(cws[pid][tid].begin(), cws[pid][tid].end());
            total_cws_amount += cws[pid][tid].size();
            // for (auto cws: cws[pid][tid]) {
            //     cws.display();
            // }
        }
    }
    cout << "cws amount: " << total_cws_amount << endl;
}

void getQuerySeq(vector<vector<int>> &docs, vector<int> &querySeq) {
    querySeq.assign(docs[0].begin(), docs[0].end());
}

void getSignature(vector<int> &seq, vector<int> &signature, pair<int, int> hf) {
    vector<int> minimal(k, numeric_limits<int>::max());
    for (int pid = 0; pid < k; pid++) {
        signature[pid] = tokenNum;
    }
    for (int i = 0; i < seq.size(); i++) {
        int v = eval(hf, seq[i]);
        if (v < minimal[v / (m / k)]) {
            minimal[v / (m / k)] = v;
            signature[v / (m / k)] = seq[i];
        }
    }
}

void groupbyTid(unordered_map<int, vector<CW>> &tidToCW, vector<int> &signature, vector<vector<vector<CW>>> &cws) {
    for (int pid = 0; pid < k; pid++) {
        for (auto cw: cws[pid][signature[pid]]) {
            tidToCW[cw.T].push_back(cw);
        }
    }
}

void generateUpdates(unordered_map<int, vector<CW>> &tidToCW, unordered_map<int, vector<Update>> &tidToUpdates) {
    for (auto item: tidToCW) {
        int tid = item.first;
        vector<CW>& cws = item.second;
        for (auto cw: cws) {
            if (cw.c == -1) {
                tidToUpdates[tid].emplace_back(cw.l, cw.l, cw.r, 0, 1);
                tidToUpdates[tid].emplace_back(cw.r + 1, cw.l, cw.r, 0, -1);
            }
            else {
                tidToUpdates[tid].emplace_back(cw.l, cw.c, cw.r, 1, 1);
                tidToUpdates[tid].emplace_back(cw.c + 1, cw.c, cw.r, 1, -1);
            }
        }
        sort(tidToUpdates[tid].begin(), tidToUpdates[tid].end());
    }
}

void nearDupSearch(vector<vector<int>> &docs, unordered_map<int, vector<Update>> &tidToUpdates, double threshold, unordered_map<int, vector<tuple<int, int, int, int>>> &results) {
    SegmentTree segtree;
    for (auto item: tidToUpdates) {
        int tid = item.first;
        vector<Update>& updates = item.second;

        map<int, int> discret; 
        vector<int> rev;
        rev.push_back(0);
        for (auto update: updates) {
            // printf("%d %d %d\n", update.t, update.l, update.r);
            discret.insert(make_pair(update.l, 0));
            discret.insert(make_pair(update.r, 0));
        }
        int cnt = 0;
        for (auto &it: discret) {
            it.second = ++cnt;
            rev.push_back(it.first);
        }        

        segtree.init(cnt);
        segtree.build(1, 1, cnt);

        for (int i = 0; i < updates.size(); i++) {
            Update update = updates[i];
            if (i > 0 && updates[i].t != updates[i - 1].t) {
                vector<pair<int, int>> Rranges;
                segtree.query(1, 1, cnt, k * threshold, Rranges);
                for (auto Rrange: Rranges) {
                    results[tid].emplace_back(make_tuple(updates[i - 1].t, updates[i].t - 1, rev[Rrange.first], rev[Rrange.second]));
                }
                // printf("%d\n", Rranges.size());
            }
            if (update.type == 0) {
                segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value * threshold);
            }
            else {
                segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value);
            }
            
            if (i == updates.size() - 1) {
                vector<pair<int, int>> Rranges;
                segtree.query(1, 1, cnt, k * threshold, Rranges);
                for (auto Rrange: Rranges) {
                    results[tid].emplace_back(make_tuple(updates[i].t, docs[tid].size(), rev[Rrange.first], rev[Rrange.second]));
                }
                // printf("%d\n", Rranges.size());
            }
        }
    }
}

void statistics(unordered_map<int, vector<tuple<int, int, int, int>>> &results) {
    cout << "results text amount: " << results.size() << endl;
    // for (auto result: results) {
    //     cout << "tid: " << result.first << endl;
    //     for (auto tu: result.second) {
    //         cout << "[" << get<0>(tu) << ", " << get<1>(tu) << "] * [" << get<2>(tu) << ", " << get<3>(tu) << "]" << endl;
    //     }
    // }
}

std::chrono::_V2::system_clock::time_point timer;

void timerStart() {
    timer = chrono::high_resolution_clock::now();
}

double timerCheck() {
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - timer);
    return duration.count() / 1000000.0;
}

int main() {
    string scr_dir = "/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/";
    string src_file = "/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin";
    
    timerStart();
    vector<vector<int>> docs;
    loadBin(src_file, docs);
    int doc_num = docs.size();
    cout << "Doc number: " << doc_num << endl;
    cout << "Load Time: " << timerCheck() << endl;


    timerStart();
    pair<int, int> hf = generateHF();
    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum + 1)); //cws[partition][token][]
    buildCW(docs, cws, hf);
    cout << "CW Generation Time: " << timerCheck() << endl;

    timerStart();
    sortCW(cws);
    cout << "CW Sorting Time: " << timerCheck() << endl;
    
    vector<int> querySeq, signature(k);
    getQuerySeq(docs, querySeq);
    getSignature(querySeq, signature, hf);

    timerStart();
    unordered_map<int, vector<CW>> tidToCW;
    groupbyTid(tidToCW, signature, cws);

    unordered_map<int, vector<Update>> tidToUpdates;
    generateUpdates(tidToCW, tidToUpdates);

    unordered_map<int, vector<tuple<int, int, int, int>>> results;
    nearDupSearch(docs, tidToUpdates, threshold, results);

    cout << "Query Time: " << timerCheck() << endl;

    statistics(results);

    return 0;
}