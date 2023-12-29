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
#include "../src/util/IO.hpp"
#include "../src/util/cw.hpp"
#include "../src/util/update.hpp"
#include "../src/util/segTree.hpp"
#include "../src/util/Hasher.hpp"
#include "../src/util/stopwordsFilter.hpp"
#include "../src/util/util.hpp"
#include <omp.h>

using namespace std;

ofstream ofs;

int doc_num;
int doc_length = 0;
int INTERVAL_LIMIT = 40;
int k = 64;
int min_seq_len;
string src_file;
string index_file;
const int tokenNum = 50257;

const double eps = 1e-10;
const string stpwords_path = "/research/projects/zp128/SearchDuplicate/filtered_tokens.bin";
StopwordsFilter filter(stpwords_path);

// Function to compute signatures for sliding windows in a set of sequences.
// seqs: The input sequences.
// signatures: The output vector of signatures for each window.
// hf: The vector of hash functions.
// win_len: The length of the sliding window.
void slideWinAndGetSig(vector<vector<int>> &seqs, vector<vector<int>> &windows, unsigned int win_len, unsigned int stride)
{

    windows = vector<vector<int>>();

    unsigned int seq_cnt = 0;
    for (auto &seq : seqs)
    {
        seq_cnt++;
        if (seq.size() < win_len)
            continue;
        int tmp_cnt = 0;
        for (size_t i = 0; i < seq.size(); i += stride)
        {   
            tmp_cnt++;
            if (i + win_len >= seq.size())
                break;
            auto begin = seq.begin() + i;
            auto end = begin + win_len;
            if (filter.countNonStopwords(begin, end) >= min_seq_len) // if there are too little nonstopwords
                windows.emplace_back(vector<int>(begin, end));
            else{
                printf("%d.%d is omited because its almost all are stopwords\n",seq_cnt-1,tmp_cnt-1  );
            }
        }
    }
}


int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "f:n:k:i:l:q:L:")) != EOF) {
        switch (opt) {
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
    if(doc_num==0){
        loadBin(src_file, docs);
    }else{
        if (doc_length == 0)
            loadBin(src_file, docs, doc_num);
        else
            loadBin(src_file, docs, doc_num, doc_length);
        cout << "Load Time: " << timerCheck(load_st) << endl;
    }
    

    // Generate Comapct Windows
    vector<vector<int>> windows;
    min_seq_len = k / 4;
    unsigned int slide_len = 128;
    unsigned int win_stride = 64;
    slideWinAndGetSig(docs, windows, slide_len, win_stride);
    string testquerypath = "./test_query.bin";
    writeBin(windows, testquerypath);
    return 0;
}