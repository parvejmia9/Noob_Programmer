#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ext_gcd(ll a, ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll x1,y1;
    ll g=ext_gcd(b,a%b,x1,y1);
    x=y1;
    y=x1-y1*(a/b);
    return g;
}
bool diophan(ll a,ll b, ll c,ll &x,ll &y, ll &g){
    g=ext_gcd(abs(a),abs(b),x,y);
    if(c%g) return 0;
    x*=(c/g);
    y*=(c/g);
    if(a<0) x=-x;
    if(b<0) y=-y;
    return 1;
}
void shift_sol(ll &x, ll &y,ll a, ll b, ll cnt){
    x+=(cnt*b); /// actually this b is b/gcd
    y-=(cnt*a);/// actually this a is a/gcd
}
ll find_all_sol(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy,ll &lx, ll &rx){
    ll x,y,g;
    if(!diophan(a,b,c,x,y,g)){
        return 0;
    }
    a/=g;
    b/=g;
    ll sign_a = a > 0 ? +1 : -1;
    ll sign_b = b > 0 ? +1 : -1;
    ll lx1,rx1,lx2,rx2;
    shift_sol(x,y,a,b,(minx-x)/b);
    if(x<minx) shift_sol(x,y,a,b,sign_b);
    if(x>maxx) return 0;
    lx1=x;
    shift_sol(x,y,a,b,(maxx-x)/b);
    if(x>maxx) shift_sol(x,y,a,b,-sign_b);
    rx1=x;
    shift_sol(x,y,a,b,-(miny-y)/a);
    if(y<miny) shift_sol(x,y,a,b,-sign_a);
    if(y>maxy) return 0;
    lx2=x;
    shift_sol(x,y,a,b,-(maxy-y)/a);
    if(y>maxy) shift_sol(x,y,a,b,sign_a);
    rx2=x;
    if (lx2 > rx2) swap(lx2, rx2);
    lx=max(lx1,lx2);
    rx=min(rx1,rx2);
    if(lx>rx) return 0;
    return (rx-lx)/b+1;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,c,a,b;
    cin >>n>>c>>a>>b;
    if(c==0){
        cout<<"0 0 "<<n<<'\n';
    }
    else{
        ll lx,rx;
        ll ans=find_all_sol(a,b,c,0,n,0,n,lx,rx);
        if(ans==0){
            cout<<"-1\n";
        }
        else{
                //cout<<lx<<' '<<rx<<endl;
            ll x=lx;
            ll y=(c-a*lx)/b;
            if(a==b && (x+y)>n){
                return cout<<"-1\n",0;
            }
            ll k=0;
            if(a>b){
                k=ans-1;
            }
            shift_sol(x,y,a,b,k);
            if(x+y>n){
                return cout<<"-1\n",0;
            }
            cout<<x<<' '<<y<<' '<<(n-x-y)<<'\n';
        }
    }
}
