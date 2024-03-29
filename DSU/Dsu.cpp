struct DSU {
    vector<int> par, sz; // this also means the root of each set
    vector<bool> vis;
    int connected;
    int n;
    void set(int d) {
        n = d;
        connected=n;
        par.resize(n, -1);
        sz.resize(n, 0);
        vis.resize(n, 0);
    }
    void make_set(int x) {
        par[x] = x;
        sz[x] = 1;
    }
    int find_set(int x) {
        if (par[x] == x) {
            return x;
        }
        return par[x] = find_set(par[x]);
    }
    void unite(int x, int y) {
        int a = find_set(x);
        int b = find_set(y);
        if (a != b) {
            if (sz[a] > sz[b]) {
                swap(a, b);
            }
            par[a] = b; // boro size ta hobe choto size er parent
            sz[b] += sz[a]; // boro er size+= soto er size
            connected--;
        }
    }
};
