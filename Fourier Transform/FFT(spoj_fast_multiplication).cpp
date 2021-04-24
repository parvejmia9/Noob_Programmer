#include<bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
template <typename T>  using oset =
    tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;
#define odrkey order_of_key
#define fbodr find_by_order
#define ll long long
#define sq(a) ((a)*(a))
#define ull unsigned long long
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()
#define watch(x) cout << (#x) << " is " << (x) << endl
#define pi 3.1415926536
#define nwl cout <<"\n";
#define MAXN 10000001
#define ff first
#define ss second
#define pb push_back
ll Pow(ll a, ll b) {
	if (a == 0) return 0LL;
	ll ans = 1;
	for (int i = 0; i < b; i++) {
		ans *= a;
	}
	return ans;
}
ll lcm(ll a, ll b) {
	return (a * b) / __gcd(a, b);
}
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
typedef vector<ll> VI;
double PI = acos(0) * 2;

class Complex { //  C must be in uppercase
public:
    double a, b;
    Complex() {a = 0.0; b = 0.0;}
    Complex(double na, double nb) {a = na; b = nb;}
    const Complex operator+(const Complex &c) const
    {return Complex(a + c.a, b + c.b);}
    const Complex operator-(const Complex &c) const
    {return Complex(a - c.a, b - c.b);}
    const Complex operator*(const Complex &c) const
    {return Complex(a * c.a - b * c.b, a * c.b + b * c.a);}
    double magnitude() {return sqrt(a * a + b * b);}
    void print() {printf("(%.3f %.3f)\n", a, b);}
};

class FFT {
public:
    vector<Complex> data;
    vector<Complex> roots;
    VI rev;
    int s, n;

    void setSize(int ns) {
        s = ns;
        n = (1 << s);
        int i, j;
        rev = VI(n);
        data = vector<Complex> (n);
        roots = vector<Complex> (n + 1);
        for (i = 0; i < n; i++)
            for (j = 0; j < s; j++)
                if ((i & (1 << j)) != 0)
                    rev[i] += (1 << (s - j - 1));
        roots[0] = Complex(1, 0);
        Complex mult = Complex(cos(2 * PI / n), sin(2 * PI / n));
        for (i = 1; i <= n; i++)
            roots[i] = roots[i - 1] * mult;
    }

    void bitReverse(vector<Complex> &array) {
        vector<Complex> temp(n);
        int i;
        for (i = 0; i < n; i++)
            temp[i] = array[rev[i]];
        for (i = 0; i < n; i++)
            array[i] = temp[i];
    }

    void transform(bool inverse = false) {
        bitReverse(data);
        int i, j, k;
        for (i = 1; i <= s; i++) {
            int m = (1 << i), md2 = m / 2;
            int start = 0, increment = (1 << (s - i));
            if (inverse) {
                start = n;
                increment *= -1;
            }
            Complex t, u;
            for (k = 0; k < n; k += m) {
                int index = start;
                for (j = k; j < md2 + k; j++) {
                    t = roots[index] * data[j + md2];
                    index += increment;
                    data[j + md2] = data[j] - t;
                    data[j] = data[j] + t;
                }
            }
        }
        if (inverse)
            for (i = 0; i < n; i++) {
                data[i].a /= n;
                data[i].b /= n;
            }
    }
    // need the co efficient
    // warning: precision errors
    static VI convolution(VI &a, VI &b) {
        int alen = a.size(), blen = b.size();
        int resn = alen + blen - 1; // size of the resulting array
        int s = 0, i;
        while ((1 << s) < resn) s++;    // n = 2^s
        int n = 1 << s; // round up the the nearest power of two
        FFT pga, pgb;
        pga.setSize(s); // fill and transform first array
        for (i = 0; i < alen; i++) pga.data[i] = Complex(a[i], 0);
        for (i = alen; i < n; i++)  pga.data[i] = Complex(0, 0);
        pga.transform();
        pgb.setSize(s); // fill and transform second array
        for (i = 0; i < blen; i++)  pgb.data[i] = Complex(b[i], 0);
        for (i = blen; i < n; i++)  pgb.data[i] = Complex(0, 0);
        pgb.transform();
        for (i = 0; i < n; i++) pga.data[i] = pga.data[i] * pgb.data[i];
        pga.transform(true);    // inverse transform
        VI result = VI (resn);  // round to nearest integer
        for (i = 0; i < resn; i++)  result[i] = (ll) (pga.data[i].a + 0.5);
        int actualSize = resn - 1;  // find proper size of array
        while (result[actualSize] == 0)
            actualSize--;
        if (actualSize < 0) actualSize = 0;
        result.resize(actualSize + 1);
        return result;
    }
    // for multiplying only dont't need the co efficient
    static vector<bool> convolution(vector<bool> &a, vector<bool> &b) {
        int alen = a.size(), blen = b.size();
        int resn = alen + blen - 1; // size of the resulting array
        int s = 0, i;
        while ((1 << s) < resn) s++;    // n = 2^s
        int n = 1 << s; // round up the the nearest power of two

        FFT pga, pgb;
        pga.setSize(s); // fill and transform first array
        for (i = 0; i < alen; i++) pga.data[i] = Complex(a[i], 0);
        for (i = alen; i < n; i++)  pga.data[i] = Complex(0, 0);
        pga.transform();

        pgb.setSize(s); // fill and transform second array
        for (i = 0; i < blen; i++)  pgb.data[i] = Complex(b[i], 0);
        for (i = blen; i < n; i++)  pgb.data[i] = Complex(0, 0);
        pgb.transform();

        for (i = 0; i < n; i++) pga.data[i] = pga.data[i] * pgb.data[i];
        pga.transform(true);    // inverse transform
        vector<bool> result = vector<bool> (resn);  // round to nearest integer
        for (i = 0; i < resn; i++)  result[i] = (int) (pga.data[i].a + 0.5);

        int actualSize = resn - 1;  // find proper size of array
        while (result[actualSize] == 0)
            actualSize--;
        if (actualSize < 0) actualSize = 0;
        result.resize(actualSize + 1);
        return result;
    }
};
vector<ll> polyadd(vector<ll> a, vector<ll> b) {
    while (a.size() < b.size())a.pb(0);
    while (b.size() < a.size())b.pb(0);
    vector<ll> res;
    for (int i = 0; i < a.size(); i++) {
        res.pb(a[i] + b[i]);
    }
    return res;
}
vector<ll> polysub(vector<ll> a, vector<ll> b) {
    while (a.size() < b.size())a.pb(0);
    while (b.size() < a.size())b.pb(0);
    vector<ll> res;
    for (int i = 0; i < a.size(); i++) {
        res.pb(a[i] - b[i]);
    }
    return res;
}
vector<bool> polypow(vector<bool> a, int k) {
    if (k == 0) return {1};
    vector<bool>tm = polypow(a, k / 2);
    tm = FFT::convolution(tm, tm);
    if (k % 2) {
        tm = FFT::convolution(tm, a);
    }
    return tm;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		string a, b;
		cin >> a >> b;
		VI aa, bb;
		for (int i = (int)a.size() - 1; i >= 0; i--) aa.pb(a[i] - '0');
		for (int i = (int)b.size() - 1; i >= 0; i--) bb.pb(b[i] - '0');
		VI res = FFT::convolution(aa, bb);
		VI ans;
		int prop = 0;
		for (int i = 0; i < (int)res.size(); i++) {
			int tm = res[i] + prop;
			ans.pb(tm % 10);
			prop = tm / 10;
		}
		if (prop || ans.size() == 0) ans.pb(prop);
		reverse(all(ans));
		for (int x : ans) cout << x;
		nwl;
	}
}
