template<size_t sz>
class cmp {
// this class helps to insert bitset in map and set
//map<bitset<16>, int, cmp<16>> mp;
//set<bitset<16>, cmp<16>>s;
public:
    bool operator()(const bitset<sz>&a, const bitset<sz>&b)const {
        for (int i = sz - 1; i >= 0; i--) {
            if (a[i] == b[i]) continue;
            if (a[i] < b[i]) return 1;
            else return 0;
        }
        return 0;
    }
};
