struct edge
{
	ll nn, c, f, oppo;
	//nn= next node
	// c= capacity
	// f= flow
};

ll src, snk, lev[MAXN], nxt[MAXN], INF = 5e9;
vector<edge> graph[MAXN];

void add_edge(ll x, ll y, ll w, bool f = 1) {
	edge a = {y, w, 0, (ll)graph[y].size()};
	if (!f) w = 0;
	edge b = {x, w, 0, (ll)graph[x].size()};// undirected na hole w er jaygay 0 hobe
	graph[x].push_back(a);
	graph[y].push_back(b);
}
bool bfs() {
	memset(lev, -1, sizeof lev);
	lev[src] = 0;
	queue<ll> q;
	q.push(src);
	while (!q.empty()) {
		ll x = q.front();
		q.pop();
		for (auto tm : graph[x]) {
			ll y = tm.nn;
			if (lev[y] == -1 && tm.c > tm.f) { // capacity soto ba soman hole ami extra flow dite parbo na
				lev[y] = lev[x] + 1;
				q.push(y);
			}
		}
	}
	return lev[snk] != -1;
}
ll dfs(ll x, ll sent_flow) {
	if (x == snk) return sent_flow;
	for (; nxt[x] < graph[x].size(); nxt[x]++) { // ager node gulo check korar dorkar nai tai nxt[x] theke shuru
		ll y = graph[x][nxt[x]].nn;
		ll c = graph[x][nxt[x]].c;
		ll f = graph[x][nxt[x]].f;
		ll oppo = graph[x][nxt[x]].oppo;
		if (lev[y] == lev[x] + 1 && c > f) {
			ll tmp = dfs(y, min(sent_flow, c - f));
			if (tmp > 0) {
				graph[x][nxt[x]].f += tmp; // ei edge er flow barbe
				graph[y][oppo].f -= tmp; // opposite edge(residual) er flow kombe
				return tmp;
			}
		}
	}
	return 0;
}
void init() {
	for (int i = 0; i < MAXN; i++) {
		graph[i].clear();
		lev[i] = -1;
		nxt[i] = 0;
	}
}
ll max_flow(ll _src, ll _snk) {
	src = _src;
	snk = _snk;
	ll totalflow = 0;
	while (bfs()) {
		memset(nxt, 0, sizeof nxt);
		ll sent_flow;
		while (1) {
			sent_flow = dfs(src, INF);
			if (sent_flow == 0) break;
			totalflow += sent_flow;
		}
	}
	return totalflow;
}
