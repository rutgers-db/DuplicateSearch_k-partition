#pragma once
#include "../util/util.hpp"
#include <bits/stdc++.h>
using namespace std;

class SeedExtension
{
private:
    vector<int> query;
    vector<int> source;
    unordered_map<int, int> query_mp; // Maps tokens to their positions in the query
    vector<pair<int, int>> seeds;     // Stores seeds as pairs of positions (token, source_pos)

    int maxgap;     // Maximum gap between tokens in a cluster
    const int min_maxgap; // minimum of current maximum gap between tokens in a cluster
    int minsize;    // Minimum size of a cluster to be considered significant
    double minsim;        // similarity threshold
public:
    SeedExtension(const vector<int> &query, const vector<int> &source, int min_maxgap, double thres)
        : query(query), source(source), min_maxgap(min_maxgap), minsim(thres) {}

    void init()
    {
        // Building the unordered_map for query
        for (int i = 0; i < query.size(); ++i)
        {
            query_mp[query[i]]++;
        }

        // calculate the minsize and maxgap
        minsize = ceil(minsim*query_mp.size());
        maxgap = (1-minsim) * query_mp.size() ; // times 4 because there maybe duplicate tokens that won't count more then once when caculating jaccard
    }

    vector<pair<int, int>> run()
    {
        // Identifying seeds
        for (int j = 0; j < source.size(); ++j)
        {
            if (query_mp.find(source[j]) != query_mp.end())
            {
                seeds.emplace_back(source[j], j);
            }
        }
 
        // No way to get the result cause not enough collided
        if (seeds.size() < minsize)
        {   
            return vector<pair<int, int>>();
        }

        // Clustering seeds
        vector<pair<int, int>> clusters = extension(0, seeds.size() - 1, maxgap);

        return clusters;
    }

private:
    vector<pair<int, int>> extension(int l, int r, int tmp_maxgap)
    {
        auto clusters = clustering(l, r, tmp_maxgap);
        auto res_clusters = validation(clusters, tmp_maxgap);
        return res_clusters;
    }

    // it return the result that are subsequences of the source
    // pair.first and second indicate the range of such subsequence that in seeds
    // l and r means input seeds such from seeds[l] to seeds[r]
    vector<pair<int, int>> clustering(int l, int r, int tmp_maxgap)
    {
        vector<pair<int, int>> res;
        if (r<l)
            return res;

        // Tuple to store the start and end indices in seeds, and the number of seeds
        vector<tuple<int, int, int>> clusters;
        int start_idx = l; // Start index in seeds
        int end_idx = l;   // End index in seeds
        int seed_count = 1;

        for (int i = l; i <= r; ++i)
        {
            // Check if the current seed is within tmp_maxgap distance from the last seed
            if (seeds[i].second - seeds[end_idx].second <= tmp_maxgap)
            {
                end_idx = i;  // Update the end index of the current cluster
                ++seed_count; // Increment the seed count
            }
            else
            {
                // Finalize the current cluster
                clusters.emplace_back(start_idx, end_idx, seed_count);

                // Start a new cluster with the current seed
                start_idx = i;
                end_idx = i;
                seed_count = 1;
            }
        }

        // Add the last cluster
        clusters.emplace_back(start_idx, end_idx, seed_count);

        // Discard clusters smaller than minsize and add the remaining to the result
        res.reserve(clusters.size());
        for (const auto &cluster : clusters)
        {
            if (get<2>(cluster) >= minsize)
            {
                res.emplace_back(get<0>(cluster), get<1>(cluster));
            }
        }

        return res;
    }

    vector<pair<int, int>> validation(vector<pair<int, int>> &clusters, int maxgap)
    {
        vector<pair<int, int>> result;

        for (const auto &c : clusters)
        {
            auto c_st = source.begin() + seeds[c.first].second;
            auto c_ed = source.begin() + seeds[c.second].second;
            vector<int> subseq(c_st, c_ed);
            
            double similarity_score = jaccard_similarity(query, subseq); // Implement this function
            // cout<<seeds[c.first].second<< " -> "<<seeds[c.second].second<<" sim:"<<similarity_score<< endl;
            if (similarity_score < minsim)
            {
                if (maxgap >= min_maxgap)
                {
                    // Re-run extension with reduced maxgap
                    vector<pair<int, int>> extended = extension(c.first, c.second, maxgap - 1);
                    result.insert(result.end(), extended.begin(), extended.end());
                }
            }
            else
            {
                result.emplace_back(seeds[c.first].second, seeds[c.second].second);
            }
        }

        return result;
    }
};
