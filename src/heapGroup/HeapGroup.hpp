#pragma once
#include "IndexIterator.hpp"
using namespace std;

class HeapGroup
{
    vector<IndexIterator> indexes; // the heap
    vector<IndexIterator> queue;   // Temporary Store the fronts of the heap
    int k;
    int collision_thres;
    vector<pair<unsigned int, int>> updates; // use to linesweep
public:
    HeapGroup() {}

    void init(vector<vector<vector<CW>>> &cws, const vector<int> &signature, double thres)
    {
        k = signature.size();
        collision_thres = (int)ceil(k * thres);
        indexes.reserve(k);
        for (int pid = 0; pid < k; pid++)
        {
            indexes.emplace_back(IndexIterator(cws[pid][signature[pid]]));
        }
        // make a minimum heap
        make_heap(indexes.begin(), indexes.end(), greater<IndexIterator>());
    }

    // Based on Heap Method, Iterate the tid
    void run(unordered_map<int, vector<CW>> &tidToCW)
    {
        // Only the candidate document's cws will be pushed into this tidToCW
        // Iterate until the heap size is less than ktheta
        while (indexes.size() + queue.size() >= collision_thres)
        {
            auto min_index = indexes.front();
            // cout<<min_index.getCurDoc()<<" ";
            // Check if the index's current Doc ID matches those in the queue
            if (queue.empty() || min_index.getCurDoc() == queue.front().getCurDoc())
            {
                queue.push_back(min_index);
                pop_heap(indexes.begin(), indexes.end(), greater<IndexIterator>());
                indexes.pop_back();
            }
            else
            {
                clearQueue(tidToCW);
                // queue.push_back(min_index);
                // pop_heap(indexes.begin(), indexes.end(), greater<IndexIterator>());
                // indexes.pop_back();
            }

            if (indexes.empty())
            {
                clearQueue(tidToCW);
            }
        }
    }

    // Check if the queue has enough indexes, >= collision thres then invode all their getAllCWsInCurDoc and push them into the tidToCW
    // Then invoke all their nextDoc() and if success then push_heap
    void clearQueue(unordered_map<int, vector<CW>> &tidToCW)
    {
        if (queue.size() >= collision_thres && lineSweep())
        {
            int curDoc = queue.front().getCurDoc();
            auto &cwList = tidToCW[curDoc];
            for (auto &it : queue)
            {
                it.getAllCWsInCurDoc(cwList);
            }
        }

        // need to update that we can skip some docs
        int left_inQue = queue.size();
        bool if_next;
        for (auto &it : queue)
        {
            if (left_inQue + 1 < collision_thres)
            {
                auto cur_min_T = indexes.front().getCurDoc();
                if_next = it.nextSpecifiedDoc(cur_min_T);
            }
            else
            {
                if_next = it.nextDoc();
            }

            if (if_next)
            {
                indexes.push_back(it);
                push_heap(indexes.begin(), indexes.end(), greater<IndexIterator>());
            }

            left_inQue--;
        }
        queue.clear();
    }

private:
    bool lineSweep()
    {
        for (auto &it : queue)
        {
            updates.emplace_back(it.getCurL(), 1);
            updates.emplace_back(it.getCurR() + 1, -1);
        }
        sort(updates.begin(), updates.end());
        int cnt = 0;
        int remain_positive = updates.size();
        for (int i = 0; i < updates.size(); i++)
        {
            auto &update = updates[i];
            cnt += update.second;
            if (cnt >= collision_thres)
            {
                updates.clear();
                return true;
            }

            if (update.second == 1)
            {
                remain_positive--;
                // No way to meet the thres k    
                if (remain_positive + cnt < collision_thres)
                    break;
            }
        }
        updates.clear();
        return false;
    }
};