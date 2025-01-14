#pragma once
#include <bits/stdc++.h>
#include "../util/util.hpp"
#include "../util/segTree.hpp"
#include "cw.hpp"
#include "search.hpp"
// #define ARIBITRARY_GEN
using namespace std;
class OPH
{
private:
    Hasher &hasher;
    vector<int> query;
    vector<int> source;
    vector<int> signature; // signature
    double thres;          // similarity threshold
    int k;                 // hash function amount
    int tokenNum;          // it is also the reprensentative of Empty Token

    vector<vector<CW>> cws; // compact windows Index

public:
    vector<pair<int, int>> result;

    OPH(const vector<int> &query, const vector<int> &source, int k, double thres, Hasher &_hasher, int tokenNum) : query(query), source(source), k(k), thres(thres), hasher(_hasher), tokenNum(tokenNum)
    {
    }

    void init()
    {
        cws.resize(k);
        getSignatureOPH();

        // build the sourceument's index
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
        for (auto vec : cws)
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
            // result = nearDupSearch_longest(collide_cws, thres, k);
            result = new_nearDupSearch(collide_cws, thres, k);
        
        return collide_cws.size();
    }

private:
    void partition(const vector<pair<int, int>> &seg, const vector<int> &pos, int n, int l, int r, vector<CW> &tmp_cws, int hid)
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

        a = (l == 0) ? 0 : pos[l - 1] + 1;
        b = (r == pos.size() - 1) ? source.size() - 1 : pos[r + 1] - 1;
        auto token = source[pos[ret.second]];
        if (token == signature[hid])
        {
            tmp_cws.emplace_back(a, pos[ret.second], b);
        }
        partition(seg, pos, n, l, ret.second - 1, tmp_cws, hid);
        partition(seg, pos, n, ret.second + 1, r, tmp_cws, hid);
    }

    void emptyCW(const vector<int> &pos, vector<CW> &ecws, int source_size)
    {
        if (pos.size() == 0)
        {
            ecws.emplace_back(0, -1, source_size - 1);
            return;
        }
        if (pos[0] > 0)
        {
            ecws.emplace_back(0, -1, pos[0] - 1);
        }
        for (int i = 1; i < pos.size(); i++)
        {
            if (pos[i - 1] + 1 <= pos[i] - 1)
            {
                ecws.emplace_back(pos[i - 1] + 1, -1, pos[i] - 1);
            }
        }
        if (pos[pos.size() - 1] < source_size - 1)
        {
            ecws.emplace_back(pos[pos.size() - 1] + 1, -1, source_size - 1);
        }
    }

    void buildCW()
    {
        vector<vector<int>> pos(k);
        vector<int> hval;

        hval.resize(source.size());
        for (int i = 0; i < source.size(); i++)
        {
            hval[i] = hasher.eval(0, source[i]);
            pos[hasher.getBinId(hval[i])].emplace_back(i);
        }

        for (int hid = 0; hid < k; hid++)
        {
            vector<pair<int, int>> seg(source.size() * 2);
            const auto &tmp_pos = pos[hid];
            int n = tmp_pos.size();
            if (n > 0 && signature[hid] != tokenNum)
            {
                for (int i = 0; i < n; i++)
                {
                    seg[n + i].first = hval[tmp_pos[i]];
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
                partition(seg, tmp_pos, n, 0, n - 1, cws[hid], hid);
            }

            if (signature[hid] != tokenNum)
                continue;

            emptyCW(tmp_pos, cws[hid], source.size());
        }
    }

    // OPH Version
    void getSignatureOPH()
    {
        signature.resize(k);
        vector<int> minimal(k, numeric_limits<int>::max());
        // assume first all are empty.
        for (int hid = 0; hid < k; hid++)
        {
            signature[hid] = tokenNum;
        }

        for (auto token : query)
        {
            int v = hasher.eval(0, token); // because in OPH, only one hash function
            auto bin_id = hasher.getBinId(v);
            if (bin_id == -1)
                continue;
            if (v < minimal[bin_id])
            {
                minimal[bin_id] = v;
                signature[bin_id] = token;
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
