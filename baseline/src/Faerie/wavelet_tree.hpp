#ifndef WAVELET_TREE
#define WAVELET_TREE

#include <bits/stdc++.h>
using namespace std;

/**
 * WaveletTree is a class that implements a Wavelet Tree data structure.
 *
 * A Wavelet Tree is a balanced binary tree used to store a sequence of
 * integers while supporting various range queries efficiently. This
 * implementation allows querying the number of elements less than or equal to
 * a given value within a specified range of indices.
 * 
 * reference:
 * 1. https://www.geeksforgeeks.org/wavelet-trees-introduction/
 * 2. https://zhuanlan.zhihu.com/p/590974585
 * 
 */

// Attention all the values should be >= 0
class WaveletTree
{

private:
    class WaveletTreeNode
    {
    public:
        // Range to elements
        int low, high;

        // Left and Right child
        WaveletTreeNode *left = nullptr;
        WaveletTreeNode *right = nullptr;

        // array freq[] will store the count of the elements that will go to left and right childs of the node.
        // That is, freq[i] will denote the count of elements from the first i elements of S[] that will go to left child.
        // Therefore, count of elements that will go to right child can be easily calculated as (i – freq[i]).
        vector<int> freq;
        vector<pair<int,int>> value_id_pairs;

        ~WaveletTreeNode()
        {
            // Recursively delete the left and right child nodes.
            if (left)
            {
                delete left;
                left = nullptr;
            }
            if (right)
            {
                delete right;
                right = nullptr;
            }
        }

        // Constructor: from and to are vector iterators pointing to the beginning and end of the data segment
        // x and y are the minimum and maximum values in the data
        WaveletTreeNode(vector<pair<int, int>>::iterator from, vector<pair<int, int>>::iterator to, int x, int y)
        {
            low = x;
            high = y;

            // Base case: empty data segment
            if (from >= to)
            {
                return;
            }

            // Base case: all elements in the data segment are the same
            if (high == low)
            {
                freq.reserve(to - from + 1);
                freq.push_back(0);
                for (auto it = from; it != to; it++)
                {
                    freq.push_back(freq.back() + 1);
                }
                return;
            }

            // Calculate the middle value of the current range
            int mid = (low + high) / 2;
            auto lessThanMid = [mid](pair<int, int> x)
            {
                return x.first <= mid;
            };

            // Initialize the frequency vector
            freq.reserve(to - from + 1);
            freq.push_back(0);

            // Initialize the value_id_pairs vector
            value_id_pairs.reserve(to - from + 1);
            value_id_pairs.emplace_back(-1, -1);

            for (auto it = from; it != to; it++)
            {
                freq.push_back(freq.back() + lessThanMid(*it));
                value_id_pairs.push_back(*it);
            }

            // Partition the data around the middle value
            auto pivot = stable_partition(from, to, lessThanMid);

            // Construct the left and right child trees recursively
            left = new WaveletTreeNode(from, pivot, low, mid);
            right = new WaveletTreeNode(pivot, to, mid + 1, high);
        }

        // Query function: count the number of elements in the range of indice [l, r] (assume indice starts from 1) less than or equal to k
        int kOrLess(int l, int r, int k)
        {
            // Base case: empty range or k is less than the minimum value in the range
            if (l > r || k < low)
            {
                return 0;
            }

            // Base case: k is greater than or equal to the maximum value in the range
            if (high <= k)
            {
                return r - l + 1;
            }

            // LtCount = freq[ L-1 ] (i.e. elements going to left sub-tree from L-1) , RtCount = freq[ R ] (i.e. elements going to right sub-tree from R)
            // The reason why here using freq[l-1] is based on assume L to R have at least one element to either left child or right child
            // Therefore LtCount + 1 will be the first indice of the element that assigned to the left child in [L,R]. However, if RtCount == LtCount, it means there is no element assigned to left child.
            // It will produce a conflict and indidate that there is not element assigned to the left child. Similarly, l - LtCount (l - 1 - LtCount + 1) has the same meaning
            int LtCount = freq[l - 1];
            int RtCount = freq[r];

            // Recursively query the left and right subtrees and return the sum of the results
            return (this->left->kOrLess(LtCount + 1, RtCount, k) +
                    this->right->kOrLess(l - LtCount, r - RtCount, k));
        }

        // predInRange(𝑖, 𝑎, 𝑏) = max( { 𝑗 ≤ 𝑖 | 𝑇 [ 𝑗 ] ∈ (𝑎, 𝑏)} ∪ {−1} )
        // note that here we assume the index starts from 1
        int predInRange(int i, int a, int b)
        {
            if (a >= b || a >= high || b <= low || i <= 0){
                return -1;
            }
                

            // empty element or the leftmost element in this node is already in the right of i
            if (value_id_pairs.empty())
            {   
                return -1;
            }

            // if all elements in current ndde is in the range of (a,b)
            // if (low > a && high < b)
            if (value_id_pairs[i].first > a  && value_id_pairs[i].first < b)
            {
                // return the position
                return value_id_pairs[i].second;
            }else{
                i--;
            }

            // Calculate the middle value of the current range, so the element in the range of [low,mid] will go to left node
            // the rest of the elements go to right node
            // int mid = (low + high) / 2;

            // calculate the intersections of left range and (a,b), also right range and (a,b)
            // int left_a = max(low - 1, a);
            // int left_b = min(mid + 1, b);
            // int right_a = max(mid, a);
            // int right_b = min(high + 1, b);

            // Recursively query the left and right subtrees and return the sum of the results
            return max(this->left->predInRange(freq[i], a, b),
                       this->right->predInRange(i - freq[i], a, b));
        }

        // succInRange(𝑖, 𝑎, 𝑏) = min( { 𝑗 ≥ 𝑖 | 𝑇 [ 𝑗 ] ∈ (𝑎, 𝑏)} ∪ {𝑛} )
        // note that here we assume the index starts from 1
        int succInRange(int i, int a, int b, const int & n)
        {
            if (a >= b || a >= high || b <= low || i <= 0 || i>= value_id_pairs.size()){
                return n;
            }
                

            // empty element or the leftmost element in this node is already in the right of i
            if (value_id_pairs.empty())
            {   
                return n;
            }

            // if all elements in current ndde is in the range of (a,b)
            // if (low > a && high < b)
            if (value_id_pairs[i].first > a  && value_id_pairs[i].first < b)
            {
                // return the position
                // if(value_id_pairs[i].second == -1)
                    // cout<<i<<" i " << value_id_pairs[i].first<<endl;
                return value_id_pairs[i].second;
            }

            // Calculate the middle value of the current range, so the element in the range of [low,mid] will go to left node
            // the rest of the elements go to right node
            // int mid = (low + high) / 2;

            // calculate the intersections of left range and (a,b), also right range and (a,b)
            // int left_a = max(low - 1, a);
            // int left_b = min(mid + 1, b);
            // int right_a = max(mid, a);
            // int right_b = min(high + 1, b);

            // Recursively query the left and right subtrees and return the sum of the results
            return min(this->left->succInRange(freq[i] + 1, a, b,n),
                       this->right->succInRange(i - freq[i] + 1, a, b,n));
        }
    };

public:
    WaveletTreeNode *root;
    int data_len;
    ~WaveletTree()
    {
        delete root;
        root = nullptr;
    }
    void deleteRoot()
    {
        delete root;
        root = nullptr;
    }
    // create_value_index_pairs function takes a const std::vector<int>& as an input,
    // iterates through the input vector, and constructs a new vector of pair<int, int> by using emplace_back to
    // efficiently insert the element value and its index as a pair into the result vector.
    vector<pair<int, int>> create_value_index_pairs(const vector<int> &input)
    {
        vector<pair<int, int>> result;

        for (size_t i = 0; i < input.size(); ++i)
        {
            result.emplace_back(input[i], i);
        }

        return result;
    }

    void build(vector<int> data)
    {
        data_len = data.size();
        // pair the index just behind the element
        auto enumerated_data = create_value_index_pairs(data);

        // get the range of the data
        int high = *max_element(data.begin(), data.end());
        int low = *min_element(data.begin(), data.end());

        // build the tree
        root = new WaveletTreeNode(enumerated_data.begin(), enumerated_data.end(), low, high);
    }

    inline int kOrLess(int l, int r, int k)
    {
        return root->kOrLess(l, r, k);
    }

    inline int predInRange(int i, int a, int b)
    {
        // that is because in the waveletTreeNode, we assume the freq and value_id_pairs always have a empty element in the front.
        // so that the index should increase 1
        i+=1;
        return root->predInRange(i, a, b);
    }

    inline int succInRange(int i, int a, int b)
    {
        i+=1;
        return root->succInRange(i, a, b, data_len);
    }
};

#endif // WAVELET_TREE