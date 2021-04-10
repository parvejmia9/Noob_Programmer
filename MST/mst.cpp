class DSU {
public:
    vector<ll>par, sz;
    int n;
    void set(int x) {
        n = x;
        par.resize(n);
        sz.resize(n);
    }
    void make_set(int x) {
        par[x] = x;
        sz[x] = 1;
    }
    int find_set(int x) {
        return (par[x] == x ? x : par[x] = find_set(par[x]));
    }
    void unite(int x, int y) {
        int a = find_set(x);
        int b = find_set(y);
        if (a != b) {
            if (sz[a] > sz[b]) {
                swap(a, b);
            }
            par[a] = b;
            sz[b] += sz[a];
        }
    }
};
bool cmp(tuple<ll, ll, ll>a, tuple<ll, ll, ll>b) {
    ll w1, w2;
    tie(ignore, ignore, w1) = a;
    tie(ignore, ignore, w2) = b;
    return w1 < w2;
}
class MST {
public:
    int n;
    void set(int d) {
        n = d;
    }
    ll cost = 0;
    vector<tuple<ll, ll, ll>>mst_edges;
    bool find_mst(vector<tuple<ll, ll, ll>>&edges) {
        DSU ds;
        ds.set(n);
        for (int i = 0; i < n; i++) ds.make_set(i);
        sort(all(edges), cmp);
        for (auto tp : edges) {
            int a, b, w;
            tie(a, b, w) = tp;
            if (ds.find_set(a) != ds.find_set(b)) {
                cost += w;
                ds.unite(a, b);
                mst_edges.pb(tp);
            }
        }
        for (int i = 1; i < n; i++) {
            if (ds.find_set(i) != ds.find_set(i - 1)) return 0;// after kruskal the resulting graph is disconnected
        }
        return 1;// if we found the mst then return 1
    }
};
