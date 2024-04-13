#pragma once
#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <vector>

using namespace std;

class Hasher {
    int m;
    int k;
    mt19937 mt_rand;
    vector<pair<int, int>> HF;

public:
static const int p = 998244353;
    Hasher() {
    }

    Hasher(int k) : k(k), mt_rand(0) {
        m = p / k * k;
        generateHF();
    }

    void generateHF() {
        HF.clear();
        for (int i = 0; i < k; i++) {
            HF.emplace_back(mt_rand() % p, mt_rand() % p);
        }
    }

    int eval(int hid, int x) {
        auto & hf = HF[hid];
        return (1LL * x * hf.first + hf.second) % p % m;
    }

    const vector<pair<int, int>>& getHF() const {
        return HF;
    }

    inline int getBinId(int x){
        if(x == numeric_limits<int>::max())
            return -1;
        return x/ (m / k);
    }
    // Method to print hash functions
    void printHF() const {
        cout << "Hash Functions (HF):" << endl;
        for (int i = 0; i < HF.size(); ++i) {
            cout << "HF[" << i << "]: (" << HF[i].first << ", " << HF[i].second << ")" << endl;
        }
    }

};
