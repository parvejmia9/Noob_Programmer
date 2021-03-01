bool vis[sz];
ll sum[sz];
vector<ll> smallest_prime(sz);
void seive() {
	for (int i = 2; i < sz; i += 2) {
		smallest_prime[i] = 2;
		vis[i] = 1;
	}
	for (ll i = 3; i < sz; i += 2) {
		if (!vis[i]) {
			smallest_prime[i] = i;
			for (ll j = i; (j * i) < sz; j += 2) {
				if (!vis[i * j]) {
					vis[i * j] = 1;
					smallest_prime[i * j] = i;
				}
			}
		}
	}
}
void factorize(ll n) {// n<=10^7 er jonno kaaj korbe
	vector<int> v;
  // ei v tei amar factor gula store hobe
  // n=20 er jonnpo store hobe v={2,2,5}; sort korle
	while (n > 1) {
		v.push_back(smallest_prime[n]);
		n /= smallest_prime[n];
	}
}
