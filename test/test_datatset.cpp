#include <bits/stdc++.h>
#include "../src/util/IO.hpp"
#include "../src/util/util.hpp"
#include "../src/util/cw.hpp"
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

    // load index
    auto load_st = timerStart();
    vector<vector<vector<CW>>> cws(k, vector<vector<CW>>(tokenNum + 1)); // cws[partition][token][]
    loadCW(index_file, cws);
    cout << "CW Loading Time: " << timerCheck(load_st) << endl;
    auto query_st = timerStart();

#pragma omp parallel for
    for (int pid = 0; pid < k; pid++)
    {
        for(int tid = 0; tid < cws[pid].size(); tid++){
            auto & cw_list = cws[pid][tid];
            int cur_T = -1;
            int l,r;
            for (auto cw : cw_list)
            {
                if (cw.T != cur_T)
                {
                    l = cw.l;
                    r = cw.r;
                    cur_T = cw.T;
                }else{
                    if(cw.l<l || cw.r > r){
                        cout<<"Problem here in "<< cw.l<< " "<<l<<" "<< cw.r<<" "<<r<<endl;
                        break;
                    }
                }
            }
        }
    }

    double total_cost = timerCheck(query_st);
    cout << "Traversing Whole Index cost : " << total_cost << endl;
    return 0;
}