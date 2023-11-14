#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <unordered_map>
#include <assert.h>
#include "IO.hpp"
#include "cw.hpp"
// #include "segTree.hpp"

using namespace std;

const int tokenNum = 50257;

const int INTERVAL_LIMIT = -1;
const int p = 998244353;
const int k = 10;
const int m = p / k * k;

// mt19937 mt_rand(time(0));
mt19937 mt_rand(0);

pair<int, int> generateHF() {
    return make_pair(mt_rand() % p, mt_rand() % p);
}

int eval(pair<int, int> hf, int x) {
    return (1LL * x * hf.first + hf.second) % p % m;
}

void partition(int doc_id, vector<int> &doc, vector<pair<int, int>> &seg, vector<int> &pos, int n, int l, int r, vector<vector<CW>> &cws) {
    if (l + INTERVAL_LIMIT >= r)
        return;

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

    assert(doc[pos[ret.second]] >= 0 && doc[pos[ret.second]] < tokenNum);
    cws[doc[pos[ret.second]]].emplace_back(doc_id, l, pos[ret.second], r);
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
    if (pos.size() < doc_size - 1) {
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
            if (seg.size() < 2 * n) {
                seg.resize(2 * n);
                // cout << "seg size: " << seg.size() << endl;
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
            emptyCW(doc_id, pos[pid], cws[pid][tokenNum], doc.size());
        }
    }
    
}


void sortCW(vector<vector<vector<CW>>> &cws) {
    int total_cws_amount = 0;
    for (int pid = 0; pid < k; pid++) {
        for (int tid = 0; tid <= tokenNum; tid++) {
            sort(cws[pid][tid].begin(), cws[pid][tid].end());
            total_cws_amount += cws[pid][tid].size();
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

int main() {
    string scr_dir = "/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/";
    string src_file = "/research/projects/zp128/dataset_tokenizedGbt2/tokenized_bin/openwebtext_gpt2.bin";
    
    vector<vector<int>> docs;
    loadBin(src_file, docs);
    int doc_num = docs.size();

    pair<int, int> hf = generateHF();

    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum + 1)); //cws[partition][token][]
    buildCW(docs, cws, hf);
    sortCW(cws);
    
    // vector<int> querySeq, signature(k);
    // getQuerySeq(docs, querySeq);
    // getSignature(querySeq, signature, hf);
    
    // unordered_map<int, vector<CW>> tidToCW;
    // groupbyTid(tidToCW, signature, cws);
    return 0;
}