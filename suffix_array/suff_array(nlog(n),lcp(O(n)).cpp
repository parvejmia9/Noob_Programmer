
// this fun will return the suffix array
vector<int> suff_array_build(string s) {
	s += '$';
	int n = s.size();
	int mx = 256;
	vector<int> sa(n);//suffix array
	vector<int> p(n), c(n), cnt(max(n, mx));
	for (char ch : s) cnt[ch]++;
	for (int i = 1; i < mx; i++) cnt[i] += cnt[i - 1];
	for (int i = 0; i < n; i++) p[--cnt[s[i]]] = i;
	int classes = 1;
	c[p[0]] = 0;
	for (int i = 1; i < n; i++) {
		if (s[p[i - 1]] != s[p[i]]) classes++;
		c[p[i]] = classes - 1;
	}
	// initialized finished
	int h = 0;
	vector<int> pn(n), cn(n);
	while ((1 << h) < n) {
		for (int i = 0; i < n; i++) {
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0) pn[i] += n;
		}
		fill(cnt.begin(), cnt.begin() + classes, 0);
		for (int i = 0; i < n; i++) {
			cnt[c[pn[i]]]++;
		}
		for (int i = 1; i < classes; i++) {
			cnt[i] += cnt[i - 1];
		}
		for (int i = n - 1; i >= 0; i--) {
			p[--cnt[c[pn[i]]]] = pn[i];
		}

		classes = 1;
		cn[p[0]] = 0;
		for (int i = 1; i < n; i++) {
			int pos1 = (p[i] + (1 << h)) - n;
			int pos2 = (p[i - 1] + (1 << h)) - n;
			if (pos1 < 0) pos1 += n;
			if (pos2 < 0) pos2 += n;
			pair<int, int> cur = {c[p[i]], c[pos1]};
			pair<int, int> prev = {c[p[i - 1]], c[pos2]};
			if (cur != prev) classes++;
			cn[p[i]] = classes - 1;
		}
		c.swap(cn);
		h++;
	}
	//p.erase(p.begin());
	return p;
}
// this will return the lpc array of (i,i+1) i->0....n-1
// but if we want lcp(i,j) where lcp(i,j) means lcp of p[i] suffix and p[j] suffix;
// then we have to find the min(lcp[i] to lcp[j-1])  j>i; we can use rmq;
// if the problem if we nedd only lcp array we will use O(n) implementation of lcp array;
// else we will use the nlog(n) implementation

vector<int> lcp_array(string const& s, vector<int> const& p) {
	int n = s.size();
	vector<int> rnk(n, 0);
	for (int i = 0; i < n; i++)
		rnk[p[i]] = i;

	int k = 0;
	vector<int> lcp(n - 1, 0);
	for (int i = 0; i < n; i++) {
		if (rnk[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = p[rnk[i] + 1];
		while (i + k < n && j + k < n && s[i + k] == s[j + k])
			k++;
		lcp[rnk[i]] = k;
		if (k)
			k--;
	}
	return lcp;
}
