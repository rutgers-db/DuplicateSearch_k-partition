#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "cw.hpp"

using namespace std;

void loadBin(const string &binFileName, vector<vector<int>> &docs) {
    ifstream ifs(binFileName, ios::binary);
    if (!ifs) {
        cout << "error open bin file" << endl;
        return;
    }
    int size;
    // int limit = 10, num = 0;
    while (ifs.read((char *)&size, sizeof(int))) {
        vector<int> vec(size);
        ifs.read((char *)&vec[0], sizeof(int) * size);
        docs.emplace_back(vec);
        // printf("Binary File %s Read, whose has %d texts\n", binFileName.c_str(), size);
        // if (++num == limit)
        //     break;
    }
    ifs.close();
}

void loadCW(const string &binFileName, vector<vector<vector<CW>>> &cws) {
    ifstream ifs(binFileName, ios::binary);
    if (!ifs) {
        cout << "error open bin file" << endl;
        return;
    }
    int par_num, token_num, cw_num;
    ifs.read((char *)&par_num, sizeof(int));
    ifs.read((char *)&token_num, sizeof(int));
    cws.resize(par_num);
    for (int pid = 0; pid < par_num; pid++) {
        for (int tid = 0; tid < token_num; tid++) {
            cws[pid].resize(token_num + 1);
            ifs.read((char *)&cw_num, sizeof(int));
            for (int i = 0; i < cw_num; i++) {
                ifs.read((char *)&cws[pid][tid][i], sizeof(CW));
            }
        }
    }
}

void saveCW(const string &binFileName, vector<vector<vector<CW>>> &cws) {
    ofstream ofs(binFileName, ios::binary);
    if (!ofs) {
        cout << "error open bin file" << endl;
        return;
    }
    int par_num = cws.size(), token_num = cws[0].size() - 1, cw_num;
    ofs.write((char*)&par_num, sizeof(int));
    ofs.write((char*)&token_num, sizeof(int));
    for (int pid = 0; pid < par_num; pid++) {
        for (int tid = 0; tid < token_num; tid++) {
            cw_num = cws[pid][tid].size();
            ofs.write((char *)&cw_num, sizeof(int));
            for (int i = 0; i < cw_num; i++) {
                ofs.write((char *)&cws[pid][tid][i], sizeof(CW));
            }
        }
    }
}