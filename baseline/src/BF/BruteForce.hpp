#include <algorithm> // for std::max
#include <cmath>     // for std::ceil
#include <iostream>  // for std::cout
#include <unordered_set>
#include <vector>

using namespace std;

class BruteForce {
private:
private:
    const vector<int>& query;
    const vector<int>& source;
    unordered_set<int> querySet; // Set representation of the query
    unordered_set<int> subsequenceSet; // Set representation of the current subsequence of source
    size_t intersectionSize = 0; // Number of elements common to querySet and subsequenceSet
    double threshold;
    double lastSim = 0; // Last calculated similarity
    int maxSize; // Maximum size of subsequenceSet to achieve threshold
    vector<pair<int, int>> results; // Store the result ranges
public:

    void resetForNewSubsequence() {
        subsequenceSet.clear();
        intersectionSize = 0;
        lastSim = 0;
    }

    // Function to calculate Jaccard similarity incrementally
   double calculateSimilarityIncrementally(int newToken) {
        if (!subsequenceSet.insert(newToken).second) {
            // Token already in subsequenceSet, no change in similarity
            return lastSim;
        } else if (querySet.find(newToken) != querySet.end()) {
            // New token is in both querySet and subsequenceSet
            ++intersectionSize;
        }

        size_t unionSize = querySet.size() + subsequenceSet.size() - intersectionSize;
        lastSim = static_cast<double>(intersectionSize) / unionSize;
        return lastSim;
    }

public:
    BruteForce(const vector<int>& query, const vector<int>& source, double threshold) :
        query(query), source(source), threshold(threshold), querySet(query.begin(), query.end()) {
        maxSize = static_cast<int>(ceil(querySet.size() / threshold));
    }

    void run() {
        for (size_t start = 0; start < source.size(); ++start) {
            resetForNewSubsequence();
            for (size_t end = start; end < source.size(); ++end) {
                if (subsequenceSet.size() > maxSize) {
                    // It's impossible to achieve the required threshold with the current subsequence
                    break;
                }

                double similarity = calculateSimilarityIncrementally(source[end]);
                if (similarity >= threshold) {
                    results.emplace_back(start, end);
                    if(start == 0){
                        cout<<start<<" "<< end<< " "<<lastSim<<" "<< querySet.size()<< " "<<subsequenceSet.size()<< " "<<intersectionSize<< endl;
                    }
                }
            }
        }
    }

    vector<pair<int, int>> filterOverlappingRanges() {
        if (results.empty()) return {};

        sort(results.begin(), results.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) {
                 return a.first < b.first || (a.first == b.first && a.second > b.second);
             });

        vector<pair<int, int>> filteredResults;
        pair<int, int> current = results[0];

        for (size_t i = 1; i < results.size(); ++i) {
            if (results[i].first <= current.second) {
                // Extend the current range if the next one overlaps
                current.second = max(current.second, results[i].second);
            } else {
                filteredResults.push_back(current);
                current = results[i];
            }
        }
        filteredResults.push_back(current); // Add the last range

        return filteredResults;
    }

    // Getter for the results
    const vector<pair<int, int>>& getResults() const {
        return results;
    }
};
