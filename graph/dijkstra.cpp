// 1 based
// if 0 based write par[src]=-1;
vector<pair<ll, ll>> graph[MAXN];
ll dis[MAXN];
int par[MAXN];
void dijkstra(int src) {
	dis[src] = 0;
	par[src] = 0;
	priority_queue<pair<ll, ll>>pq;
	pq.push({0, src});
	while (!pq.empty()) {
		ll node, w;
		tie(w, node) = pq.top();
		pq.pop();
		w *= -1;
		if (dis[node] < w) continue;
		for (auto p : graph[node]) {
			if (dis[p.ff] > dis[node] + p.ss) {
				dis[p.ff] = dis[node] + p.ss;
				par[p.ff] = node;
				pq.push({ -dis[p.ff], p.ff});
			}
		}
	}
}
