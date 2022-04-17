class SG {
public:
	int n;
	vector<int>t;
	void set(int d) {
		n = d;
		t.resize(2 * n + 1, 0);
	}
	void build() {  // build the tree
		for (int i = n - 1; i > 0; --i) t[i] = (t[i << 1] + t[i << 1 | 1]);
	}
	void modify(int p, int value) {
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = (t[p] + t[p ^ 1]);
	}
	int query(int l, int r) {  // sum on interval [l, r)
		int res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += t[l++];
			if (r & 1) res += t[--r];
		};
		return res;
	}
 
};
