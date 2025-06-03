#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

map<ll,ll> HM;
const ll nils = 1000000007;
const ll LOG = 40;
int n;
vl A;

ll h(ll x){
    if(x == 0)return 0;
    if(HM.find(x) != HM.end())return HM[x];
    HM[x] = ll(rand()) * nils + ll(rand());
    return HM[x];
}

ll solve_fast(vl &A){
    vl B;
    sort(all(A));
    rep(c1,0,sz(A)){
        B.push_back(A.back()+1-A[c1]);
    }
    reverse(all(B));

    ll ans = 1;
    for(ll x = LOG; x >= 0; x--){
        ll xo = 0;
        trav(b, B){
            if(b != 0)xo ^= h((b-1)%(1ll << x)+1);
        }
        if(xo == 0){
            ans += (1ll << x);
            rep(c1,0,sz(B)){
                B[c1] = max(0ll, B[c1]-(1ll << x));
            }
        }
        else{
            rep(c1,0,sz(B)){
                if(B[c1] != 0)B[c1] = ((B[c1]-1)%(1ll << x)+1);
            }
        }
    }
    return ans;
}

int main() { 

    cin >> n;
    rep(c1,0,n){
        ll a;
        cin >> a;
        A.push_back(a);
    }
    cout << solve_fast(A) << "\n";

    return 0;
}