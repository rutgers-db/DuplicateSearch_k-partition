#pragma once
#include <bits/stdc++.h>
#include "../util/util.hpp"
#include "../util/segTree.hpp"
#include "cw.hpp"
#include "search.hpp"
using namespace std;
// #define ARIBITRARY_GEN

class KMINS
{
private:
    Hasher &hasher;
    vector<int> query;
    vector<int> source;
    vector<int> signature; // signature
    double thres;          // similarity threshold
    int k;                 // hash function amount

    vector<vector<CW>> cws; // compact windows Index

public:
    vector<pair<int, int>> result;

    KMINS(const vector<int> &query, const vector<int> &source, int k, double thres, Hasher &_hasher) : query(query), source(source), k(k), thres(thres), hasher(_hasher)
    {
    }

    void init()
    {
        cws.resize(k);
        getSignatureKMINS();

        // build the document's index
        buildCW();
    }

    unsigned int run(bool if_intervalscan, bool if_longest)
    {
        // No way to get the result cause not enough collided
        size_t collide_lim = ceil(k * thres);
        int cnt = 0;
        for (auto vec : cws)
        {
            cnt += vec.size() == 0 ? 0 : 1;
        }
        if (cnt < collide_lim)
        {
            return 0;
        }

        vector<CW> collide_cws;
        for (auto &vec : cws)
        {
            collide_cws.insert(collide_cws.end(), vec.begin(), vec.end());
        }

        if (if_intervalscan == true){
            if(if_longest)
                result = OutterScan_longest(collide_cws, thres, k);
            else
                result = OutterScan(collide_cws, thres, k);
        }
        else
            result = new_nearDupSearch(collide_cws, thres, k);
        
        return collide_cws.size();
    }

private:
    void partition(vector<pair<int, int>> &seg, const int &n, int l, int r, int hid)
    {
        if (l > r)
            return;
        pair<int, int> ret(numeric_limits<int>::max(), numeric_limits<int>::max());
        int a = l, b = r;
        for (a += n, b += n; a <= b; ++a /= 2, --b /= 2)
        {
            if (a % 2 == 1)
#ifdef ARIBITRARY_GEN
            if (seg[a].first < ret.first)
            #else
            if (seg[a] < ret)
            #endif
                    ret = seg[a];
            if (b % 2 == 0)
#ifdef ARIBITRARY_GEN
            if (seg[b].first < ret.first)
            #else
            if (seg[b] < ret)
            #endif
                    ret = seg[b];
        }

        auto token = source[ret.second];
        if (token == signature[hid])
        {
            cws[hid].emplace_back(l, ret.second, r);
        }

        partition(seg, n, l, ret.second - 1, hid);
        partition(seg, n, ret.second + 1, r, hid);
    }

    void buildCW()
    {
        for (int hid = 0; hid < k; hid++)
        {
            vector<pair<int, int>> seg(source.size() * 2);
            vector<int> hval(source.size());
            int n = source.size();
            for (int i = 0; i < source.size(); i++)
            {
                hval[i] = hasher.eval(hid, source[i]);
            }

            // build segment tree
            for (int i = 0; i < n; i++)
            {
                seg[n + i].first = hval[i];
                seg[n + i].second = i;
            }
            for (int i = n - 1; i; i--)
            {
#ifdef ARIBITRARY_GEN
                if (seg[2 * i].first < seg[2 * i + 1].first)
#else
                if (seg[2 * i] < seg[2 * i + 1]) // Attention, if you wana choose the left most when facing a tie
#endif
                    seg[i] = seg[2 * i];
                else
                    seg[i] = seg[2 * i + 1];
            }
            partition(seg, n, 0, n - 1, hid);
        }
    }

    void getSignatureKMINS()
    {
        signature.resize(k);
        for (int hid = 0; hid < k; hid++)
        {
            int tmp_min = numeric_limits<int>::max();
            for (auto token : query)
            {
                int v = hasher.eval(hid, token);
                if (v < tmp_min)
                {
                    tmp_min = v;
                    signature[hid] = token;
                }
            }
        }
    }

public:
    vector<pair<int, int>> filter_covered_ranges()
    {
        vector<pair<int, int>> filtered_result;
        if (result.size() == 0)
        {
            return filtered_result;
        }

        // Sort the ranges
        sort(result.begin(), result.end(), [](const pair<int, int> &a, const pair<int, int> &b)
             { return a.first < b.first || (a.first == b.first && a.second > b.second); });

        pair<int, int> current_range = result[0];

        for (size_t i = 1; i < result.size(); ++i)
        {
            if (result[i].first <= current_range.second)
            {
                // Current range covers the next one, update the end if necessary
                current_range.second = max(current_range.second, result[i].second);
            }
            else
            {
                // Add the current range to the filtered result and update the current range
                filtered_result.push_back(current_range);
                current_range = result[i];
            }
        }

        // Add the last range
        filtered_result.push_back(current_range);

        return filtered_result;
    }
};
