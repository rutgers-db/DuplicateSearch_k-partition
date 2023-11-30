#pragma once
#include <vector>
using namespace std;

class SegmentTree {
    vector<float> tag, minv, maxv;
    int size;
public:

    SegmentTree(int _size = 1000){
        tag.resize((_size << 2) + 10);
        minv.resize((_size << 2) + 10);
        maxv.resize((_size << 2) + 10);
        size = _size;
    }

    ~SegmentTree() {}

    void init(int _size) {
        if (_size > size) {
            tag.resize((_size << 2) + 10);
            minv.resize((_size << 2) + 10);
            maxv.resize((_size << 2) + 10);
            size = _size;
        }
    }

    void build(int node, int L, int R) {
        if (L == R) {
            tag[node] = 0;
            minv[node] = 0;
            maxv[node] = 0;
            return;
        }
        int mid = (L + R) >> 1;
        build(node << 1, L, mid);
        build(node << 1 | 1, mid + 1, R);
        push_up(node);
    }

    void push_up(int node) {
        maxv[node] = max(maxv[node << 1], maxv[node << 1 | 1]);
        minv[node] = min(minv[node << 1], minv[node << 1 | 1]);
    }

    void push_down(int node) {
        if (tag[node] != 0) {
            tag[node << 1] += tag[node];
            tag[node << 1 | 1] += tag[node];
            minv[node << 1] += tag[node];
            minv[node << 1 | 1] += tag[node];
            maxv[node << 1] += tag[node];
            maxv[node << 1 | 1] += tag[node];
            tag[node] = 0;
        }
    }

    void query(int node, int L, int R, float val, vector<pair<int, int>> &ranges) {
        if (minv[node] > val) {
            ranges.emplace_back(L, R);
            return;
        }
        if (maxv[node] < val) {
            return;
        }
        if (L == R) {
            return;
        }
        push_down(node);
        int mid = (L + R) >> 1;
        query(node << 1, L, mid, val, ranges);
        query(node << 1 | 1, mid + 1, R, val, ranges);
    }

    int queryLongest(int node, int L, int R, float val) {
        if (minv[node] > val) {
            return R;
        }
        if (maxv[node] < val) {
            return -1;
        }
        push_down(node);
        int mid = (L + R) >> 1;
        int ret = queryLongest(node << 1 | 1, mid + 1, R, val);
        if (ret == -1)
            return queryLongest(node << 1, L, mid, val);
        else
            return ret;
    }

    void update(int node, int L, int R, int LL, int RR, float val) {
        if (LL <= L && R <= RR) {
            tag[node] += val;
            minv[node] += val;
            maxv[node] += val;
            return;
        }
        push_down(node);
        int mid = (L + R) >> 1;
        if (LL <= mid) update(node << 1, L, mid, LL, RR, val);
        if (RR > mid) update(node << 1 | 1, mid + 1, R, LL, RR, val);
        push_up(node);
    }
};