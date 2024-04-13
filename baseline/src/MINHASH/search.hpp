#pragma once

#include <bits/stdc++.h>
#include "update.hpp"
#include <omp.h>
#include "../util/segTree.hpp"
using namespace std;
const double eps = 1e-5;

SegmentTree trees[128];

// This Scan can be used to OPH and Kmins Both
void InnerScan_longest(vector<CW> &cws, unordered_set<int> &ids, double threshold, int &Rlongest, int k)
{
    vector<pair<int, double>> updates;
    updates.resize(2*ids.size());
    int rev_cnt = updates.size() - 1;
    for (auto id: ids) {
        if (cws[id].c == -1)
        {
            updates[rev_cnt--] = make_pair(cws[id].r, threshold);
            updates[rev_cnt--] = make_pair(cws[id].l - 1, -threshold);
        }
        else
        {
            updates[rev_cnt--] = make_pair(cws[id].r, 1.0);
            updates[rev_cnt--] = make_pair(cws[id].c - 1, -1.0);
        }
    }

    sort(updates.begin(), updates.end(), [](const pair<int, double>& a, const pair<int, double>& b) {
        return a > b;
    });
    
    double cnt = 0;
    for (int i = 0; i < updates.size(); i++)
    {
        auto &update = updates[i];
        if (i > 0 && updates[i].first != updates[i - 1].first)
        {
            if (cnt >= k * threshold - eps )
            {   
                
                Rlongest = updates[i - 1].first;
                // if(Rlongest == 69630){
                //     for(auto pair: updates){
                //         cout<<pair.first<<" "<<pair.second<<endl;
                //     } cout<<"One time Over "<<Rlongest<<endl;
                // }
                return;
            }
        }
        cnt += update.second;
    }
}

vector<pair<int, int>> OutterScan_longest(vector<CW> &cws, double threshold, int k)
{   
    vector<pair<int, int>> res;
    vector<Update> updates;
    for (int i = 0; i < cws.size(); i++)
    {
        CW &cw = cws[i];
        if (cw.c == -1)
        {
            updates.emplace_back(cw.l, 0, 0, i, threshold);
            updates.emplace_back(cw.r + 1, 0, 0, i, -threshold);
        }
        else
        {
            updates.emplace_back(cw.l, 0, 0, i, 1.0);
            updates.emplace_back(cw.c + 1, 0, 0, i, -1.0);
        }
    }
    sort(updates.begin(), updates.end());

    unordered_set<int> ids;
    double cnt = 0;
    for (int i = 0; i < updates.size(); i++)
    {
        Update &update = updates[i];
        if (i > 0 && updates[i].t != updates[i - 1].t)
        {
            if (cnt >= k * threshold - eps)
            {
                int Rlongest = -1;
                InnerScan_longest(cws, ids, threshold, Rlongest, k);
                if (Rlongest != -1)
                {
                    res.emplace_back(updates[i - 1].t, Rlongest);
                }
            }
        }
        cnt += update.value;
        if (update.value > 0)
        {
            ids.insert(update.type);
        }
        else
        {
            ids.erase(update.type);
        }
    }

    return res;
}

void InnerScan(vector<CW> &cws, unordered_set<int> &ids, double threshold, vector<pair<int, int>> &Rranges, int k) {
    vector<pair<int, double>> updates;
    for (auto id: ids) {
        if (cws[id].c == -1)
        {
           updates.emplace_back(cws[id].l, threshold);
            updates.emplace_back(cws[id].r + 1, -threshold);
        }
        else
        {
            updates.emplace_back(cws[id].c, 1.0);
            updates.emplace_back(cws[id].r + 1, -1.0);
        }
    }
    sort(updates.begin(), updates.end());
    double cnt = 0;
    for (int i = 0; i < updates.size(); i++) {
        auto & update = updates[i];
        if (i > 0 && updates[i].first != updates[i - 1].first) {
            if (cnt >= k * threshold - eps) {
                Rranges.emplace_back(updates[i - 1].first, updates[i].first - 1);
            }
        }
        cnt += update.second;
    }
}


vector<pair<int, int>> OutterScan(vector<CW> &cws, double threshold, int k)
{   
    // to meet the upper layer, here we not use tuple<int,int,int,int>
    // to count the time they are the same.
    vector<pair<int, int>> results;
    vector<Update> updates;
    for (int i = 0; i < cws.size(); i++)
    {
        CW &cw = cws[i];
        if (cw.c == -1)
        {
            updates.emplace_back(cw.l, 0, 0, i, threshold);
            updates.emplace_back(cw.r + 1, 0, 0, i, -threshold);
        }
        else
        {
            updates.emplace_back(cw.l, 0, 0, i, 1.0);
            updates.emplace_back(cw.c + 1, 0, 0, i, -1.0);
        }
    }
    sort(updates.begin(), updates.end());
    
    unordered_set<int> ids;
    double cnt = 0;
    for (int i = 0; i < updates.size(); i++) {
        Update& update = updates[i];
        if (i > 0 && updates[i].t != updates[i - 1].t) {
            if (cnt >= k * threshold - eps) {
                vector<pair<int, int>> Rranges;
                InnerScan(cws, ids, threshold, Rranges, k);
                for (auto Rrange: Rranges) {
                    results.emplace_back(updates[i - 1].t, Rrange.second);
                }
            }
        }
        cnt += update.value;
        if (update.value > 0)
        {
            ids.insert(update.type);
        }
        else
        {
            ids.erase(update.type);
        }
    }
    return results;
    
}

vector<pair<int, int>> new_nearDupSearch(vector<CW> &cws, float threshold, int k)
{
    vector<pair<int, int>> res;
    

    vector<Update> updates;
    updates.reserve(cws.size() * 2);
    int max_r = 0;
    for (int i = 0; i < cws.size(); i++)
    {
        CW &cw = cws[i];
        max_r = max(max_r, cw.r);
        if (cw.c == -1)
        {
            updates.emplace_back(cw.l, 0, 0, i, threshold);
            updates.emplace_back(cw.r + 1, 0, 0, i, -threshold);
        }
        else
        {
            updates.emplace_back(cw.l, 0, 0, i, 1.0);
            updates.emplace_back(cw.c + 1, 0, 0, i, -1.0);
        }
    }
    sort(updates.begin(), updates.end());
    
    // map<int, int> discret;
    // vector<int> rev;
    // rev.emplace_back(0);
    // for (auto update : updates)
    // {
    //     discret.insert(make_pair(update.l, 0));
    //     discret.insert(make_pair(update.r, 0));
    // }
    // int cnt = 0;
    // for (auto &it : discret)
    // {
    //     it.second = ++cnt;
    //     rev.emplace_back(it.first);
    // }

    unordered_map<int, int> ids;
    max_r++;
    // segtree.init(max_r);
    auto tid = omp_get_thread_num();
    auto & segtree = trees[tid];
    segtree.build(max_r);
    // segtree.init(cnt);
    // segtree.build(1, 1, cnt);

    float update_cnt = 0;
    for (int i = 0; i < updates.size(); i++)
    {   
        if (i > 0 && updates[i].t != updates[i - 1].t)
        {
            if (update_cnt >= k * threshold)
            {   
                for(auto &pair : ids){
                    if(pair.second == 0) continue;
                    const auto& cw = cws[pair.first]; double val; int tmp_l;
                    if(cw.c == -1){
                        val = threshold;
                        tmp_l = cw.l;
                    }else{
                        val = 1.0;
                        tmp_l = cw.c;
                    }
                    val = val * pair.second;
                    segtree.update(1, 1, max_r, tmp_l+1, cw.r+1, val);
                    // segtree.update(1, 1, cnt, discret[tmp_l], discret[cw.r], val);
                }
                ids.clear();

                int Rlongest = -1;
                segtree.queryLongest(1, 1, max_r, k * threshold, Rlongest);
                if (Rlongest != -1){
                    res.emplace_back(updates[i - 1].t, Rlongest-1);
                    //  res.emplace_back(updates[i - 1].t, rev[Rlongest]);
                }
                   
            }
        }

        // segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value);
        const auto & update = updates[i];
        update_cnt = update_cnt + update.value;
        if (update.value > 0)
        {
            ids[update.type]++;   
        }
        else
        {
            ids[update.type]--;
        }
        // if(ids[update.type] == 0){
        //     ids.erase(update.type);
        // }
    }

    return res;
}

// vector<pair<int, int>> nearDupSearch_longest(vector<CW> &cws, float threshold, int k)
// {
//     vector<pair<int, int>> res;
//     // SegmentTree segtree;

//     vector<Update> updates;
//     for (auto cw : cws)
//     {
//         if (cw.c == -1)
//         {
//             updates.emplace_back(cw.l, cw.l, cw.r, 0, threshold);
//             updates.emplace_back(cw.r + 1, cw.l, cw.r, 0, -threshold);
//         }
//         else
//         {
//             updates.emplace_back(cw.l, cw.c, cw.r, 1, 1.0);
//             updates.emplace_back(cw.c + 1, cw.c, cw.r, 1, -1.0);
//         }
//     }
//     sort(updates.begin(), updates.end());

//     map<int, int> discret;
//     vector<int> rev;
//     rev.emplace_back(0);
//     for (auto update : updates)
//     {
//         discret.insert(make_pair(update.l, 0));
//         discret.insert(make_pair(update.r, 0));
//     }
//     int cnt = 0;
//     for (auto &it : discret)
//     {
//         it.second = ++cnt;
//         rev.emplace_back(it.first);
//     }

//     // segtree.init(cnt);
//     segtree.build(cnt);

//     float update_cnt = 0;
//     for (int i = 0; i < updates.size(); i++)
//     {
//         Update update = updates[i];
//         if (i > 0 && updates[i].t != updates[i - 1].t)
//         {
//             if (update_cnt >= k * threshold)
//             {
//                 int Rlongest = -1;
//                 segtree.queryLongest(1, 1, cnt, k * threshold, Rlongest);
//                 if (Rlongest != -1)
//                     res.emplace_back(updates[i - 1].t, rev[Rlongest]);
//             }
//         }
//         segtree.update(1, 1, cnt, discret[update.l], discret[update.r], update.value);
//         update_cnt = update_cnt + update.value;
//     }

//     return res;
// }