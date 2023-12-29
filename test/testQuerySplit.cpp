
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

using namespace std;

// make sure the seeds are the same
mt19937 mt_rand(0);

int k = 32;
const int tokenNum = 50257;
const int p = 998244353;
const double eps = 1e-10;
const int m = p / k * k;

unsigned int slide_len = 128;
unsigned int win_stride = 64;
string index_file = "/research/projects/zp128/OPH_Align/Dataset_Construction/Owt/index/openwebtext_k32fullindex.bin";
string src_file = "/research/projects/zp128/SelfGenerationText/gpt2-medium-540L_50TOPK_400000S.bin";

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

void getQuerySeqs(vector<vector<int>> &querySeqs, string query_bin_file) {
    loadBin(query_bin_file, querySeqs);
}

// Function to compute the signature of a sequence defined by a range [begin, end).
// begin: Iterator to the beginning of the range.
// end: Iterator to the end of the range.
// signature: The output vector where the signature will be stored.
// hf: The vector of hash functions, represented as pairs of integers.
template <typename Iterator>
void getSignature(Iterator& begin, Iterator& end, vector<int> &signature, const vector<pair<int, int>> &hf)
{
    for (int hid = 0; hid < k; hid++)
    {
        unsigned int tmp_min = numeric_limits<int>::max();
        for (auto it = begin; it != end; ++it)
        {
            int v = eval(hf[hid], *it);
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
void slideWinAndGetSig(vector<vector<int>> &seqs, vector<vector<int>> &signatures, vector<pair<unsigned int, unsigned int>> &win_pos, const vector<pair<int, int>> &hf, unsigned int win_len, unsigned int stride){
    unsigned int total_win_num = 0;
    for (auto &seq : seqs) {
        if(seq.size() < win_len) continue;
        total_win_num += (seq.size() - win_len) / stride + 1;
    }

    signatures = vector<vector<int>>(total_win_num, vector<int>(k));
    win_pos.resize(total_win_num);
    total_win_num = 0;

    unsigned int seq_cnt = 0;
    for (auto &seq : seqs) {
        seq_cnt++;
        if(seq.size() < win_len) continue;
        int tmp_cnt = 0;
        for (size_t i = 0; i < seq.size(); i += stride)
        {   
            if(i+win_len >= seq.size()) break;
            auto begin = seq.begin() + i;
            auto end = begin + win_len;
            getSignature(begin, end, signatures[total_win_num], hf);
            win_pos[total_win_num++] = make_pair(seq_cnt - 1,tmp_cnt++);
        }
    }
    assert(total_win_num == win_pos.size());
}

int main(){
    // laod query sequences
    vector<vector<int>> querySeqs; 
    getQuerySeqs(querySeqs, src_file);
    vector<pair<int, int>> hf = generateHF();
    vector<vector<int>> signatures;
    vector<pair<unsigned int,unsigned int>> sig_info;
    timerStart();
    slideWinAndGetSig(querySeqs, signatures, sig_info, hf, slide_len, win_stride);
    cout << "Hashing Query: " << timerCheck() << endl;
    // ofstream ofs;
//     ofs.open("./log.txt", std::ofstream::out);
// #pragma omp parallel for
    for (int i = 0; i < signatures.size() ; i++) {
        for(int j = 0; j< signatures[i].size() ;j++){
            cout<< signatures[i][j]<<" ";
        }cout<<endl;
    }
}