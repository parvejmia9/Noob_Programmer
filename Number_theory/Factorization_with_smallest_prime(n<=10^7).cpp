bool vis[MAXN];
vector<int> smallest_prime(MAXN);
void seive() {
	for (int i = 2; i < MAXN; i += 2) {
		smallest_prime[i] = 2;
		vis[i] = 1;
	}
	for (ll i = 3; i < MAXN; i += 2) {
		if (!vis[i]) {
			smallest_prime[i] = i;
      vis[i]=1;
			for (ll j = i; (j * i) < MAXN; j += 2) {
				if (!vis[i * j]) {
					vis[i * j] = 1;
					smallest_prime[i * j] = i;
				}
			}
		}
	}
}
vector<int> factorize(ll n) {
	vector<int> v;
	while (n > 1) {
		v.push_back(smallest_prime[n]);
		n /= smallest_prime[n];
	}
	sort(all(v));
  return v; // this is the prime factors vector (here will be 2 2 2 if n has 2^3 , 5 5 if n has 5^2)
}
