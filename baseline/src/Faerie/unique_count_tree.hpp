#pragma once

// Including the header file for the WaveletTree class
#include "wavelet_tree.hpp"

// Including necessary libraries from the C++ Standard Library
#include <unordered_map>
#include <vector>
using namespace std;

// UniqueCountTree class to count unique elements within a specified range
class UniqueCountTree {
private:
  WaveletTree wavelet_tree; // An instance of WaveletTree for processing queries
  vector<int> pre_sameNum_pos; // Stores the latest position of the same number
                               // encountered in the array

public:
  // Constructor that initializes the UniqueCountTree with the provided data
  UniqueCountTree(const vector<int> &data) {
    build(data);
  }

  UniqueCountTree(){}

  void build(const vector<int> &data){
    unordered_map<int, int>
        ele_pos; // Maps each element to its latest position in 'data'
    pre_sameNum_pos.resize(
        data.size() + 1); // Resize pre_sameNum_pos to match the size of 'data'

    pre_sameNum_pos[0] = 0;
    // Iterate through the data to fill 'pre_sameNum_pos' with positions of
    // previous occurrences
    for (size_t i = 0; i < data.size(); ++i) {
      if (ele_pos.count(data[i])) {
        // If the element has been encountered before, store the previous
        // position
        pre_sameNum_pos[i + 1] = ele_pos[data[i]];
      } else {
        // If it's the first occurrence, mark as -1
        pre_sameNum_pos[i + 1] = 0;
      }
      // Update the latest position of the current element
      ele_pos[data[i]] = i + 1;
    }

    // Build the wavelet tree with the positions of previous occurrences
    wavelet_tree.build(pre_sameNum_pos);
  }

  // Function to count unique elements in the range [L, R]
  int range_unique_count(int L, int R) {
    // Delegate the query to the wavelet tree, considering elements before L as
    // "less than"
    return wavelet_tree.kOrLess(L + 2, R + 2, L);
  }
};
