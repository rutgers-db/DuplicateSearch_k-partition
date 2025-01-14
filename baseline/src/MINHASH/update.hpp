#pragma once
class Update {
public:
    int t, l, r, type; double value;

    Update(int _t, int _l, int _r, int _type, double _value) :
        t(_t), l(_l), r(_r), type(_type), value(_value) {
    }
    bool operator < (const Update &rhs) const {
        return t < rhs.t;
    }

    // Overload the << operator to allow printing with cout
    friend std::ostream& operator << (std::ostream &os, const Update &update) {
        os << "t: " << update.t << ", l: " << update.l << ", r: " << update.r
           << ", type: " << update.type << ", value: " << update.value;
        return os;
    }
    
};