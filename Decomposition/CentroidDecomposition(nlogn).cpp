/// decomposition part


/// 0 INDEXED BASED///

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
        graph[a].push_back(b);
        graph[b].push_back(a);
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
    void decompose(int x = 0, int p = -1) { // we will star from arbitary node x=0 and find the centroids
        find_size(x);
        int ct = find_centroid(x, -1, sz[x]);
        vis[ct] = 1; // to not to interfare it's child centroid to it
        par[ct] = p; // we can store many info here( we can create a struct to store
        
        /* here we can
            
         do some stuffs*/
      
        for (int y : graph[ct]) {
            if (!vis[y]) decompose(y, ct);
        }
    }

};

// lca part


struct lca_lift {
    const int lg = 24;
    int n;
    vector<int> depth;
    vector<vector<int> > edges;
    vector<vector<int> > lift;

    void set(int sz) {
        n = sz;
        depth = vector<int>(n);
        edges = vector<vector<int> >(n, vector<int>());
        lift = vector<vector<int> >(n, vector<int>(lg, -1));
    }

    void add_edge(int a, int b) {
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    void attach(int node_to_attach, int node_to_attach_to) {
        int a = node_to_attach, b = node_to_attach_to;
        add_edge(a, b);

        lift[a][0] = b;

        for (int i = 1; i < lg; i++) {
            if (lift[a][i - 1] == -1) lift[a][i] = -1;
            else lift[a][i] = lift[lift[a][i - 1]][i - 1];
        }

        depth[a] = depth[b] + 1;
    }

    void init_lift(int v = 0) {
        depth[v] = 0;
        dfs(v, -1);
    }

    void dfs(int v, int par) {
        lift[v][0] = par;

        for (int i = 1; i < lg; i++) {
            if (lift[v][i - 1] == -1) lift[v][i] = -1;
            else lift[v][i] = lift[lift[v][i - 1]][i - 1];
        }

        for (int x : edges[v]) {
            if (x != par) {
                depth[x] = depth[v] + 1;
                dfs(x, v);
            }
        }
    }

    int get(int v, int k) {
        for (int i = lg - 1; i >= 0; i--) {
            if (v == -1) return v;
            if ((1 << i) <= k) {
                v = lift[v][i];
                k -= (1 << i);
            }
        }
        return v;
    }

    int get_lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int d = depth[a] - depth[b];
        int v = get(a, d);
        if (v == b) {
            return v;
        } else {
            for (int i = lg - 1; i >= 0; i--) {
                if (lift[v][i] != lift[b][i]) {
                    v = lift[v][i];
                    b = lift[b][i];
                }
            }
            return lift[b][0];
        }
    }

    int get_dist(int a, int b) {
        int v = get_lca(a, b);
        return depth[a] + depth[b] - 2 * depth[v];
    }
};
