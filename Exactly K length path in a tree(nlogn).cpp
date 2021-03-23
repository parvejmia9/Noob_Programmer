#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>  using oset =
    tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;
#define odrkey order_of_key
#define fbodr find_by_order
#define ll long long
#define sq(a) ((a)*(a))
#define ull unsigned long long
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define watch(x) cout << (#x) << " is " << (x) << endl
#define pi 3.1415926536
#define endl "\n"
#define nwl cout << endl
#define MAXN 200009
#define ff first
#define ss second
#define pb push_back
ll Pow(ll a, ll b) {
    if (a == 0) return 0LL;
    ll ans = 1;
    for (int i = 0; i < b; i++) {
        ans *= a;
    }
    return ans;
}
ll lcm(ll a, ll b) {
    return (a * b) / __gcd(a, b);
}
ll md = (ll) 1e9 + 7;
ll bigmod(ll a, ll b, ll m) {
    if (b == 0) return 1LL;
    ll tm = bigmod(a, b / 2, m);
    tm = (tm * tm) % m;
    if (b % 2) tm = (tm * a) % m;
    return tm;
}
ll ncr(ll n, ll r) {
    if (r > n - r) r = n - r;
    ll up = 1;
    ll down = 1;
    for (ll i = 0; i < r; i++) {
        up = (up * (n - i)) % md; /* md== mod */
        down = (down * (r - i)) % md;
    }
    return (up * bigmod(down, md - 2, md)) % md;
}
vector<map<ll, ll>>v(MAXN);
int k;
int cnt[MAXN];
vector<int> level;
ll ans;
ll a[MAXN];
struct Centroid {
    vector<vector<int>>graph;// we will take initial graph in it
    vector<int> sz; // we will save save the subtree size;
    vector<int> par; //we will store the parents of the /*cetroid*/ tree nodes
    vector<bool> vis;//visited array
    int n;
    void set(int s) { // s== given node
        n = s;
        graph.resize(n, vector<int>());
        sz.resize(n, 0);
        vis.resize(n, 0);
        par.resize(n, -1);
    }
    void add_edge(int a, int b) { //to take the main graph as input
        graph[a].pb(b);
        graph[b].pb(a);
    }
    int find_size(int x = 0, int p = -1) { // we will consider 0th node as a root if node chage x to root
        if (vis[x]) return 0;
        sz[x] = 1;
        for (int y : graph[x]) {
            if (y != p) sz[x] += find_size(y, x);
        }
        return sz[x];
    }
    int find_centroid(int x, int p , int n) { // find the first centroid
        // x=arbitary node
        // p=parent
        //n= size of the subtree of x
        for (int y : graph[x]) {
            if (y != p && !vis[y] && sz[y] > (n / 2)) return find_centroid(y, x, n);
        }
        return x;
    }
    void find_level(int x, int p, int lev) {
        if (lev == k) ans++;
        level.push_back(lev);
        for (int y : graph[x]) {
            if (y != p && !vis[y]) {
                find_level(y, x, lev + 1);
            }
        }
    }
    void compute(int x) {
        vector<int> allnodes;
        for (int y : graph[x]) {
            if (!vis[y]) {
                level.clear();
                find_level(y, x, 1);
                for (int nn : level) {
                    if (nn <= k) {
                        ans += cnt[k - nn];
                    }
                    allnodes.push_back(nn);
                }
                for (int nn : level) cnt[nn]++;
            }
        }
        for (int nn : allnodes) cnt[nn]--;
    }
    void decompose(int x = 0, int p = -1) { // we will start from arbitary node x=0 and find the centroids
        find_size(x);
        int ct = find_centroid(x, -1, sz[x]);
        vis[ct] = 1; // to not to interfare it's child centroid to it
        par[ct] = p;
        compute(ct);
        for (int y : graph[ct]) {
            if (!vis[y]) decompose(y, ct);
        }
    }

};
Centroid ct;
int lca(int x, int y) {
    vector<int> a, b;
    bool ck[MAXN] = {};
    a.push_back(x);
    ck[x] = 1;
    b.pb(y);
    int tm = x;
    while (ct.par[tm] != -1) {
        tm = ct.par[tm];
        a.push_back(tm);
        ck[tm] = 1;
    }
    tm = y;
    while (ct.par[tm] != -1) {
        tm = ct.par[tm];
        b.push_back(tm);
    }
    for (int i = 0; i < (int)b.size(); i++) {
        if (ck[b[i]]) {
            return b[i];
        }
    }
}
ll query(int l , int r) {
    int lc = lca(l, r);
    // watch(v[lc][l]);
    // watch(v[lc][r]);
    return min(v[lc][l], v[lc][r]);

}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n;
    ct.set(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        ct.add_edge(a, b);
    }
    cin >> k;
    ct.decompose();
    cout << ans << endl;

}
