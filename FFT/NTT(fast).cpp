typedef long long ll;
const int N = 200009;//max degree of poly
const int mod = 998244353,G=3;
// always use constant mod for less time complexity
class NTT {
public:
	int inv_n, rev[N * 2 + 10], w[N * 2 + 10];
	int f_a[N*2+10],f_b[N*2+10];
	int bigmod(int a, int e) {
		if (e == -1) e = mod - 2;
		int ret = 1;
		while (e) {
			if (e & 1) ret = (1LL * ret * a) % mod;
			a = (1LL * a * a) % mod;
			e >>=1;
		}
		return ret;
	}
	void prepare(int n) {
		int sz = abs(31 - __builtin_clz(n));
		int r = bigmod(G, (mod - 1) / n);
		inv_n = bigmod(n, mod - 2), w[0] = w[n] = 1;
		for(int i=1;i<n;i++){
			w[i]=(1LL*w[i-1]*r)%mod;
		}
		for(int i=1;i<n;i++){
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(sz-1));
		}
	}
	void ntransform(int *a, int n,bool invt){
		for(int i=1;i<n-1;i++){
			if(i<rev[i]) swap(a[i],a[rev[i]]);
		}
		for(int m=2;m<=n;m<<=1){
			for(int i=0;i<n;i+=m){
				for(int j=0;j<(m>>1);j++){
					int &u=a[i+j],&v=a[i+j+(m>>1)];
					int t=(1LL*v*w[invt?n-n/m*j:n/m*j]%mod);
					v=u-t<0?u-t+mod:u-t;
					u=u+t>=mod?u+t-mod:u+t;
				}
			}
		}
		if(invt){
			for(int i=0;i<n;i++){
				a[i]=(1LL*a[i]*inv_n)%mod;
			}
		}
	}
	void multiply(vector<int>a,vector<int>b,vector<int>&cc){
		if(a.size()==0){
			swap(cc,b);
			return;
		}
		if(b.size()==0){
			swap(cc,a);
			return;
		}
		int sz=1,n=a.size(),m=b.size();
		while(sz<n+m-1){
			sz<<=1;
		}
		prepare(sz);
		for(int i=0;i<sz;i++){
			f_a[i]=(i<n?a[i]:0);
			f_b[i]=(i<m?b[i]:0);
		}
		ntransform(f_a,sz,0);
		ntransform(f_b,sz,0);
		for(int i=0;i<sz;i++){
			f_a[i]=(1LL*f_a[i]*f_b[i])%mod;
		}
		ntransform(f_a,sz,1);
		cc=vector<int>(f_a,f_a+n+m-1);
		while(!cc.empty() && cc.back()==0){
			cc.pop_back();
		}
	}
} ntt;
