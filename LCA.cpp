vector<int> graph[sz];
int par[sz];
int lev[sz];
bool vis[sz];
int sp[sz][20];
int dis[sz];
void dfs(int node, int l , int p) { // finding parents and levels
	vis[node] = 1;
	par[node] = p;
	lev[node] = l;
	for (int i = 0; i < graph[node].size(); i++) {
		int x = graph[node][i];
		if (!vis[x]) {
			dfs(x, l + 1, node);
		}
	}
}
void sparsh(int n) { // creating sparsh table
	for (int i = 0; i < sz; i++) {
		for (int j = 0; j < 20; j++) {
			sp[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; i++) {
		sp[i][0] = par[i];
	}
	for (int j = 1; (1 << j) < n; j++) {
		for (int i = 1; i <= n; i++) {
			if (sp[i][j - 1] != -1) {
				sp[i][j] = sp[sp[i][j - 1]][j - 1];
			}
		}
	}
}
int lca(int u, int v) { //finding lca
	if (lev[u] < lev[v]) swap(u, v);
	for (int j = 19; j >= 0; j--) {
		if ((lev[u] - (1 << j)) >= lev[v]) {
			u = sp[u][j];
		}
	}
	if (u == v) return u;
	for (int j = 19; j >= 0; j--) {
		if (sp[u][j] != -1 && (sp[u][j] != sp[v][j])) {
			u = sp[u][j], v = sp[v][j];
		}
	}
	return par[u];
}
int dist(int u, int v) { // finding distance between two node
	int l = lca(u, v);
	return lev[u] + lev[v] - 2 * lev[l];
}
