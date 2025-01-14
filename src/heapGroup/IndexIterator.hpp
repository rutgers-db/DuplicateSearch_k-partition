#pragma once
#include "../util/cw.hpp"
#include <vector>

class IndexIterator {
public:
    // Constructor takes a reference to a vector
    IndexIterator(std::vector<CW>& vec) : cw_invlist(&vec), iterator(0) {
    }

    // Iterate to the next cw whose cw.T is different or reach the end of list
    bool nextDoc() {
        if (iterator >= cw_invlist->size()) return false;

        const int currentT = (*cw_invlist)[iterator].T;
        while (iterator < cw_invlist->size() && (*cw_invlist)[iterator].T == currentT) {
            ++iterator;
        }

        return iterator < cw_invlist->size();
    }

    // Iterate to the cw whose cw.T is equal or bigger than given specified T
    bool nextSpecifiedDoc(int T) {
        if (iterator >= cw_invlist->size()) return false;
        while (iterator < cw_invlist->size() && (*cw_invlist)[iterator].T < T) {
            ++iterator;
        }

        // use lower_bound to quickly skip some documents
        // iterator = lower_bound(cw_invlist->begin() + iterator, cw_invlist->end(), CW(T,0,0,0)) - cw_invlist->begin();

        return iterator < cw_invlist->size() && (*cw_invlist)[iterator].T >= T;
    }

    // Get the current document ID
    int getCurDoc() const {
        if (iterator < cw_invlist->size()) {
            return (*cw_invlist)[iterator].T;
        }
        return -1; // Or throw an exception if preferred
    }

    // Get all the cws whose T is the same
    void getAllCWsInCurDoc(std::vector<CW>& ret) {
        if (iterator >= cw_invlist->size()) return;

        int currentT = (*cw_invlist)[iterator].T;
        while (iterator < cw_invlist->size() && (*cw_invlist)[iterator].T == currentT) {
            ret.emplace_back((*cw_invlist)[iterator]);
            ++iterator;
        }
    }

    bool if_end() const {
        return iterator >= cw_invlist->size();
    }

    // It can be tweaked later, we can directly just compare the cw itself
    bool operator>(const IndexIterator& other) const {
        return getCurDoc() > other.getCurDoc();
    }

    int getCurL(){
        auto & cw = (*cw_invlist)[iterator];
        return cw.l;
    }

    int getCurR(){
        auto & cw = (*cw_invlist)[iterator];
        return cw.r;
    }

    size_t getCwListSize(){
        return cw_invlist->size();
    }
    
private:
    std::vector<CW>* cw_invlist;
    size_t iterator;
};
