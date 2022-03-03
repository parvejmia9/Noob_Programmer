// 1 based
// if 0 based write par[src]=-1;
vector<pair<ll, ll>> graph[MAXN];
ll dis[MAXN];
int par[MAXN];
void dijkstra(int src,int n) {
	dis[src] = 0;
	par[src] = 0;
	ll dis[n];
	for (int i = 0; i < n; i++) {
		dis[i] = 1e18;
	}
	dis[0] = 0;
	priority_queue<pair<ll, ll>>pq;
	pq.push({0, 0});
	while (!pq.empty()) {
		auto p = pq.top();
		pq.pop();
		ll w = -p.ff;
		ll x = p.ss;
		if (dis[x] < w) continue;
		for (auto pp : graph[x]) {
			int y = pp.ff;
			if (dis[y] > w + pp.ss) {
				dis[y] = w + pp.ss;
				par[y]=x;
				pq.push({ -dis[y], y});
			}
		}
	}
}
