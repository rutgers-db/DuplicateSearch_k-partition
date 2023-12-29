#pragma once
#include <bits/stdc++.h>
#include "IO.hpp"
#include "Hasher.hpp"
using namespace std;

/*
    This class serves the purpose of filtering out stopwords, given the path to the bin that contains the stopwords tokens.
*/
class StopwordsFilter {
public:
    unordered_set<int> stopwords; // Stores the stopwords as an unordered set for efficient access.
    Hasher hasher;
    bool if_filter = true; // Flag to determine if filtering should be applied.

    // Default constructor.
    StopwordsFilter() {}

    // Constructor that sets the filtering flag.
    StopwordsFilter(bool _flag): if_filter(_flag) {}

    // This function loads the stopwords from the specified bin path.
    void load_stopwords(string stopwords_bin_path) {
        if (if_filter == false)
            return;

        printf("Loading stopwords from %s\n", stopwords_bin_path.c_str());
        vector<int> vec;
        // Load the stopwords from the given path and store them in the set.
        loadBin(stopwords_bin_path, vec);
        for (auto &word : vec) {
            stopwords.insert(word);
        }
    }

    void load_hasher(int k){
        hasher = Hasher(k);
        hasher.generateHF();
    }

    // Constructor that initializes the filter and loads stopwords from a given path.
    StopwordsFilter(string stopwords_bin_path) {
        if_filter = true;
        vector<int> vec;
        loadBin(stopwords_bin_path, vec);
        for (auto &word : vec) {
            stopwords.insert(word);
        }
    }

    // This function filters and erases stopwords from the given sequence.
    void const filter_erase(vector<int> &seq) {
        if (if_filter == false)
            return;

        auto it = std::remove_if(seq.begin(), seq.end(),
        [this](const int &element) {
            return this->stopwords.find(element) != this->stopwords.end();
        });
        seq.erase(it, seq.end());
    }

    // This function filters stopwords and applies a hash function to the remaining elements in the sequence.
    void const filtered_hash(vector<int> &seq, const int hid) {
        if (if_filter == false)
            return;

        std::for_each(seq.begin(), seq.end(),
        [this, &hid](int &element) {
            if (this->stopwords.find(element) != this->stopwords.end()) {
                element = INT_MAX;
            } else {
                element = hasher.eval(hid, element);
            }
        });
    }

    // This function filters a single element and applies a hash function to it.
    int const filtered_hash(int element, const int hid) {
        if (if_filter == true && this->stopwords.find(element) != this->stopwords.end()) {
            return INT_MAX;
        } else {
            return hasher.eval(hid, element);
        }
    }


    template <typename Iterator>
    size_t countNonStopwords(Iterator& begin, Iterator& end) {
        if (!if_filter) {
            return std::distance(begin, end); // If filtering is disabled, count all elements
        }

        size_t count = 0;
        for (auto it = begin; it != end; ++it) {
            if (stopwords.find(*it) == stopwords.end()) {
                ++count; // Increment count if the element is not a stopword
            }
        }
        return count;
    }

};
