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

int doc_num;
int doc_length = 0;
int INTERVAL_LIMIT = 0;
int k = 64;
string src_file;
string index_file;
string out_file;
ofstream ofs;

const int tokenNum = 50257;
const int p = 998244353;
const float eps = 1e-6;
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
    pair<int, int> ret(numeric_limits<int>::max(), numeric_limits<int>::max());
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

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "f:n:k:l:i:o:")) != EOF) {
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
            case 'i':
                index_file = optarg;
                break;
            case 'o':
                out_file = optarg;
                break;
            case '?':
                cout << optarg << endl;
                cout << opterr << endl;
                cout << "Usage: program -f bin_file_path -i index_file_path -n doc_num -k k [-l doc_length] [-L interval_limit]" << endl;
                break;
        }
    }
    ofs.open(out_file, std::ofstream::out);
    if (!ofs) {
        cout << "Error open out file" << endl;
        throw "Error open out file";
    }
    cout << "Parameters Summary: " << endl;
    cout << "bin_file_path  : " << src_file << endl;
    cout << "index_file_path: " << index_file << endl;
    cout << "out_file_path  : " << out_file << endl; 
    cout << "doc_num        : " << doc_num << endl;
    cout << "k              : " << k << endl;
    cout << "doc_length     : " << doc_length << endl;
    cout << "interval_limit : " << INTERVAL_LIMIT << endl;
    cout << "------------------------------" << endl;

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
    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum)); //cws[partition][token][]
    buildCW(docs, cws, hf);
    ofs << timerCheck() << endl;
    cout << "CW Generation Time: " << timerCheck() << endl;
    statistics(cws);
    timerStart();
    saveCW(index_file, cws, hf);
    cout << "Save cws Time: " << timerCheck() << endl;
    return 0;
}