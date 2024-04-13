#pragma once
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
// Timer Part
std::chrono::_V2::system_clock::time_point timerStart()
{
    return chrono::high_resolution_clock::now();
}

double timerCheck(std::chrono::_V2::system_clock::time_point &timer)
{
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - timer);
    return duration.count() / 1000000.0;
}

double jaccard_similarity(const std::vector<int> &text1, const std::vector<int> &text2) {
    if (text1.empty() || text2.empty()) {
        return 0.0;
    }

    std::unordered_set<int> set1(text1.begin(), text1.end());
    std::unordered_set<int> set2(text2.begin(), text2.end());

    std::vector<int> intersection;

    // Calculate intersection
    for (const auto &element : set1) {
        if (set2.find(element) != set2.end()) {
            intersection.push_back(element);
        }
    }

    // Calculate union using sets to avoid duplicates
    std::vector<int> union_set;
    union_set.reserve(set1.size() + set2.size()); // Pre-allocate memory
    union_set.insert(union_set.end(), set1.begin(), set1.end());
    union_set.insert(union_set.end(), set2.begin(), set2.end());
    std::sort(union_set.begin(), union_set.end());
    auto last = std::unique(union_set.begin(), union_set.end());
    union_set.erase(last, union_set.end()); // Remove duplicates

    // Output the sizes
    std::cout << "Size of Set 1: " << set1.size() << std::endl;
    std::cout << "Size of Set 2: " << set2.size() << std::endl;
    std::cout << "Union Size: " << union_set.size() << std::endl;
    std::cout << "Intersection Size: " << intersection.size() << std::endl;

    return static_cast<double>(intersection.size()) / union_set.size();
}