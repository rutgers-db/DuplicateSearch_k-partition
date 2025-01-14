#pragma once
#include <algorithm>

class CW {
public:
    int T, l, c, r;

    CW() {}

    CW(const int &_T, const int &_l, const int &_c, const int &_r) :
        T(_T), l(_l), c(_c), r(_r) {
    }

    CW(const CW &tmp) {
        T = tmp.T;
        l = tmp.l;
        c = tmp.c;
        r = tmp.r;
    }
    
    bool operator<(const CW &tmp) const {
        if (T == tmp.T) {
            if (c == tmp.c) {
                return l < tmp.l;
            }
            return c < tmp.c;
        }
        return T < tmp.T;
    }

    bool operator<=(const CW &tmp) const {
        if (T == tmp.T) {
            if (c == tmp.c) {
                return l <= tmp.l;
            }
            return c <= tmp.c;
        }
        return T <= tmp.T;
    }

    void display() const {
        printf("(document id: %d, l: %d, c: %d, r: %d)\n", T, l, c, r);
    }

    bool intersected(const CW &tmp)const{
        return tmp.T == T &&((l<= tmp.l && tmp.l <= r) || (r>= tmp.l && tmp.r >= r));
    }

    void merge(const CW &tmp){
        l = std::min(tmp.l,l);
        r = std::max(tmp.r,r);
    }
};