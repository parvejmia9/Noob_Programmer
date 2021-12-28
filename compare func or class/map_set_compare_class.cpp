template<size_t sz> class cmp {
// this class helps to insert bitset in map and set
//map<bitset<16>, int, cmp<16>> mp;
//set<bitset<16>, cmp<16>>s;
public:
    bool operator()(const bitset<sz>&a, const bitset<sz>&b)const {
        return a.to_ullong() < b.to_ullong();
    }
};
