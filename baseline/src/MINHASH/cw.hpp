#pragma once
#include <algorithm>

class CW
{
public:
    int l, c, r;

    CW() {}

    CW(const int &_l, const int &_c, const int &_r) : l(_l), c(_c), r(_r)
    {}

    CW(const CW &tmp)
    {
        l = tmp.l;
        c = tmp.c;
        r = tmp.r;
    }

    bool operator<(const CW &tmp) const
    {
        if (c == tmp.c)
        {
            return l < tmp.l;
        }
        return c < tmp.c;
    }

    bool operator<=(const CW &tmp) const
    {
        if (c == tmp.c)
        {
            return l <= tmp.l;
        }
        return c <= tmp.c;
    }

    void display() const
    {
        printf("( l: %d, c: %d, r: %d)\n", l, c, r);
    }

    bool intersected(const CW &tmp) const
    {
        return (l <= tmp.l && tmp.l <= r) || (r >= tmp.l && tmp.r >= r);
    }

    void merge(const CW &tmp)
    {
        l = std::min(tmp.l, l);
        r = std::max(tmp.r, r);
    }
};