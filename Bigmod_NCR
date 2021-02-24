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
