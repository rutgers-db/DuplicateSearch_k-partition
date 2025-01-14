#include <algorithm> // for std::max
#include <cmath>     // for std::ceil
#include <iostream>  // for std::cout
#include <unordered_set>
#include <vector>

#include "unique_count_tree.hpp"

using namespace std;

class Faerie {
private:
    const vector<int>& query;
    const vector<int>& source;
    vector<int> queryTokenPositions; // Positions of query tokens in source

    unordered_set<int> querySet;     // Set representation of the query
    unordered_set<int> cur_source_set; // Set representation of the tokens in current subsequence of source
    int thresholdLower, thresholdUpper, lengthThreshold; // Thresholds for pruning
    int maxNonOverlap; // Maximum allowed non-overlapping tokens
    double similarityThreshold; // Similarity threshold for matching

    UniqueCountTree uniqueTree; // Utilizes UniqueCountTree for efficient querying

    vector<pair<int, int>> result; // Stores matching ranges

    // Binary search to expand the window to the right
    void binarySpan(int startIndex, int endIndex) {
        int low = endIndex, high = queryTokenPositions.size() - 1, mid;
        while (low <= high) {
            mid = (low + high) / 2;
            if (uniqueTree.range_unique_count(queryTokenPositions[startIndex], queryTokenPositions[mid]) > thresholdUpper)
                high = mid - 1;
            else
                low = mid + 1;
        }

        findSubsequences(startIndex, high);
    }

    // Binary search to shift the window to the right when the initial window fails
    int binaryShift(int startIndex, int endIndex) {
        int low = startIndex, high = endIndex;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (uniqueTree.range_unique_count(queryTokenPositions[mid], queryTokenPositions[endIndex]) > thresholdUpper)
                low = mid + 1;
            else
                high = mid - 1;
        }
        return low;
    }

    // Finds subsequences within the given window that meet the threshold
    void findSubsequences(int i, int j) {
        // see if i to j can has minimum unique elements
        if (uniqueTree.range_unique_count(queryTokenPositions[i], queryTokenPositions[j]) < thresholdLower) {
            return;
        }

        unordered_set<int> overlappedQueryTokens;
        cur_source_set.clear();

        // Determine the left and right limits for extending the search
        int leftLimit = (i > 0) ? queryTokenPositions[i - 1] + 1 : 0;
        int rightLimit = (j == queryTokenPositions.size() - 1) ? source.size() - 1 : queryTokenPositions[j + 1] - 1;
        for (int pos = queryTokenPositions[i]; pos <= rightLimit; pos++) {
            bool sequenceFound = false;
             // Include the token if it's part of the query or a new source token
            if (!overlappedQueryTokens.count(source[pos])) {
                if (querySet.count(source[pos])) {
                    overlappedQueryTokens.insert(source[pos]);
                } else {
                    cur_source_set.insert(source[pos]);
                }
            }

            // Stop if exceeding the maximum non-overlapping tokens allowed
            if (cur_source_set.size() > maxNonOverlap) break;

            // Check if the current subsequence meets the similarity threshold
            if (overlappedQueryTokens.size() > thresholdLower && 
                (static_cast<double>(overlappedQueryTokens.size()) / (querySet.size() + cur_source_set.size())) >= similarityThreshold) {
                result.emplace_back(queryTokenPositions[i], pos);
                sequenceFound = true;
            }
                // Extend left if a valid subsequence is found
            if (sequenceFound) {
                auto left_cur_source_set = cur_source_set;
                for (int leftPos = queryTokenPositions[i] - 1; leftPos >= leftLimit; leftPos--) {
                    left_cur_source_set.insert(source[leftPos]); // Update set with potential new source tokens
                    if (left_cur_source_set.size() > maxNonOverlap) break; // Check if the extension is still valid

                    // Update results if the extended subsequence still meets the threshold
                    if (static_cast<double>(overlappedQueryTokens.size()) / (querySet.size() + left_cur_source_set.size()) >= similarityThreshold) {
                        result.emplace_back(leftPos, pos);
                    }
                }
            }

        }
    }

public:
    Faerie(const vector<int>& query, const vector<int>& source, double threshold) : 
        query(query), source(source), similarityThreshold(threshold), uniqueTree(source) {
        querySet.insert(query.begin(), query.end());

        thresholdLower = static_cast<int>(ceil(querySet.size() * similarityThreshold));
        thresholdUpper = static_cast<int>(ceil(querySet.size() / similarityThreshold));
        lengthThreshold = thresholdLower;
        maxNonOverlap = thresholdUpper - querySet.size();

        for (size_t pos = 0; pos < source.size(); ++pos) {
            if (querySet.find(source[pos]) != querySet.end()) {
                queryTokenPositions.emplace_back(pos);
            }
        }
    }

    void run() {
        int maxIndex = queryTokenPositions.size() - thresholdLower;
        for (int i = 0; i <= maxIndex; ++i) {
            int j = i + thresholdLower - 1;
            if (uniqueTree.range_unique_count(queryTokenPositions[i], queryTokenPositions[j]) <= thresholdUpper) {
                binarySpan(i, j);
                i++;
            } else {
                i = binaryShift(i, j);
            }
        }
    }

    vector<pair<int, int>> filter_covered_ranges() {
        vector<pair<int, int>> filtered_result;
        if (result.size() == 0) {
            return filtered_result;
        }

        // Sort the ranges
        sort(result.begin(), result.end(),
             [](const pair<int, int> &a, const pair<int, int> &b) {
                 return a.first < b.first || (a.first == b.first && a.second > b.second);
             });

        pair<int, int> current_range = result[0];

        for (size_t i = 1; i < result.size(); ++i) {
            if (result[i].first <= current_range.second) {
                // Current range covers the next one, update the end if necessary
                current_range.second = max(current_range.second, result[i].second);
            } else {
                // Add the current range to the filtered result and update the current
                // range
                filtered_result.push_back(current_range);
                current_range = result[i];
            }
        }

        // Add the last range
        filtered_result.push_back(current_range);

        return filtered_result;
    }
};
