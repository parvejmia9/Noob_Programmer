/** 7340033 = 7 * 2^20, G = 3
645922817 = 77 * 2^23, G = 3
897581057 = 107 * 2^23, G = 3
998244353 = 119 * 2^23, G = 3
924844033, G=5
**/
namespace NTT {
vector<int> perm, wp[2];
const int mod = 786433, G = 10;    ///G is the primitive root of M
int root, inv, NN, invN;
int power(int a, int p) {
	int ans = 1;
	while (p) {
		if (p & 1) ans = (1LL * ans * a) % mod;
		a = (1LL * a * a) % mod;
		p >>= 1;
	}
	return ans;
}
void precalculate(int n) {
	assert( (n & (n - 1)) == 0 && (mod - 1) % n == 0);
	NN = n;
	invN = power(NN, mod - 2);
	perm = wp[0] = wp[1] = vector<int>(NN);

	perm[0] = 0;
	for (int k = 1; k < NN; k <<= 1) {
		for (int i = 0; i < k; i++) {
			perm[i] <<= 1;
			perm[i + k] = 1 + perm[i];
		}
	}
	root = power(G, (mod - 1) / NN);
	inv = power(root, mod - 2);
	wp[0][0] = wp[1][0] = 1;

	for (int i = 1; i < NN; i++) {
		wp[0][i] = (wp[0][i - 1] * 1LL * root) % mod;
		wp[1][i] = (wp[1][i - 1] * 1LL * inv) % mod;
	}
}
void fft(vector<int> &v, bool invert = false) {
	if (v.size() != perm.size())   precalculate(v.size());
	for (int i = 0; i < NN; i++)
		if (i < perm[i])
			swap(v[i], v[perm[i]]);

	for (int len = 2; len <= NN; len *= 2) {
		for (int i = 0, d = NN / len; i < NN; i += len) {
			for (int j = 0, idx = 0; j < len / 2; j++, idx += d) {
				int x = v[i + j];
				int y = (wp[invert][idx] * 1LL * v[i + j + len / 2]) % mod;
				v[i + j] = (x + y >= mod ? x + y - mod : x + y);
				v[i + j + len / 2] = (x - y >= 0 ? x - y : x - y + mod);
			}
		}
	}
	if (invert) {
		for (int &x : v) x = (x * 1LL * invN) % mod;
	}
}
vector<int> multiply(vector<int> a, vector<int> b) {
	int n = 1;
	while (n < a.size() + b.size())  n <<= 1;
	a.resize(n);
	b.resize(n);
	fft(a);
	fft(b);
	for (int i = 0; i < n; i++) a[i] = (a[i] * 1LL * b[i]) % mod;
	fft(a, true);
	return a;
}
};
