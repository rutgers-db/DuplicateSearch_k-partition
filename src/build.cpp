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
#include "./util/Hasher.hpp"
#include "./util/stopwordsFilter.hpp"
#include "./util/util.hpp"
#include <omp.h>

using namespace std;

ofstream ofs;

int doc_num;
int doc_length = 0;
int INTERVAL_LIMIT = 40;
int k = 64;
string src_file;
string index_file;
const int tokenNum = 50257;

const double eps = 1e-10;
const string stpwords_path = "/research/projects/zp128/SearchDuplicate/filtered_tokens.bin";
StopwordsFilter filter(stpwords_path);

void partition(int doc_id, vector<int> &doc, vector<pair<int, int>> &seg, const int &n, int l, int r, vector<vector<CW>> &cws)
{
    if (l + INTERVAL_LIMIT > r)
        return;
    pair<int, int> ret(numeric_limits<int>::max(), numeric_limits<int>::max());
    int a = l, b = r;
    for (a += n, b += n; a <= b; ++a /= 2, --b /= 2)
    {
        if (a % 2 == 1)
            if (seg[a] < ret)
                ret = seg[a];
        if (b % 2 == 0)
            if (seg[b] < ret)
                ret = seg[b];
    }
    if (ret.first == numeric_limits<int>::max())
        return;
    cws[doc[ret.second]].emplace_back(doc_id, l, ret.second, r);
    partition(doc_id, doc, seg, n, l, ret.second - 1, cws);
    partition(doc_id, doc, seg, n, ret.second + 1, r, cws);
}

void buildCW(vector<vector<int>> &docs, vector<vector<vector<CW>>> &cws)
{
    int maxlength = 0;
    for (auto doc : docs)
    {
        maxlength = max(maxlength, int(doc.size()));
    }

#pragma omp parallel for
    for (int hid = 0; hid < k; hid++)
    {
        vector<pair<int, int>> seg(maxlength * 2);
        vector<int> hval(maxlength);
        for (int doc_id = 0; doc_id < docs.size(); doc_id++)
        {
            vector<int> &doc = docs[doc_id];
            int n = doc.size();
            for (int i = 0; i < doc.size(); i++)
            {
                hval[i] = filter.filtered_hash(doc[i], hid);
            }

            // build segment tree
            for (int i = 0; i < n; i++)
            {
                seg[n + i].first = hval[i];
                seg[n + i].second = i;
            }
            for (int i = n - 1; i; i--)
            {
                if (seg[2 * i] < seg[2 * i + 1]) // Attention, if you wana choose the left most when facing a tie
                    seg[i] = seg[2 * i];
                else
                    seg[i] = seg[2 * i + 1];
            }
            partition(doc_id, doc, seg, n, 0, n - 1, cws[hid]);
        }
    }
}

int main(int argc, char *argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "f:n:k:i:l:q:L:")) != EOF)
    {
        switch (opt)
        {
        case 'f':
            src_file = optarg;
            break;
        case 'n':
            doc_num = stoi(optarg);
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
        case 'L':
            INTERVAL_LIMIT = stoi(optarg);
            break;
        case '?':
            cout << optarg << endl;
            cout << opterr << endl;
            cout << "Usage: program -f bin_file_path -i index_path -n doc_num -k k [-l doc_length] [-L interval_limit]" << endl;
            break;
        }
    }
    cout << "Parameters Summary: " << endl;
    cout << "bin_file_path  : " << src_file << endl;
    cout << "doc_num        : " << doc_num << endl;
    cout << "k              : " << k << endl;
    cout << "doc_length     : " << doc_length << endl;
    cout << "interval_limit : " << INTERVAL_LIMIT << endl;
    cout << "------------------------------" << endl;

    cout << src_file.substr(src_file.rfind('/') + 1, src_file.rfind('.') - src_file.rfind('/') - 1) << endl;

    // stopwordsFilter laod hasher
    filter.load_hasher(k);
    filter.if_filter = true;

    // Load documents
    auto load_st = timerStart();
    vector<vector<int>> docs;
    if (doc_num == 0)
    {
        loadBin(src_file, docs);
    }
    else
    {
        if (doc_length == 0)
            loadBin(src_file, docs, doc_num);
        else
            loadBin(src_file, docs, doc_num, doc_length);
        cout << "Load Time: " << timerCheck(load_st) << endl;
    }

    // Generate Comapct Windows
    auto gen_st = timerStart();
    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum + 1)); // cws[partition][token][]
    buildCW(docs, cws);
    cout << "CW Generation Time: " << timerCheck(gen_st) << endl;

    // Write index
    saveCW(index_file, cws);
    cout << "Index file Written";
    return 0;
}