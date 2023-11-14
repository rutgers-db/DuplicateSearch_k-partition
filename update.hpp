class Update {
public:
    int t, l, r, type, value;

    Update(int _t, int _l, int _r, int _type, int _value) :
        t(_t), l(_l), r(_r), type(_type), value(_value) {
    }
    bool operator < (const Update &rhs) const {
        return t < rhs.t;
    }
};