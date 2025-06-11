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
const ll LOG = 30;
const int SQRT = 40000;
int n;
vi A;

int R[2][SQRT] = {0};

int rnd(int i, int r){
    if(R[r][i] == 0){
        R[r][i] = rand()%SQRT+1;
    }
    return R[r][i];
}

int h(int x){
    return rnd(x%SQRT, 0) * SQRT + rnd(x/SQRT, 1);
}

int solve_fast(vi &A){
    vi B;
    sort(all(A));
    rep(c1,0,sz(A)){
        B.push_back(A.back()+1-A[c1]);
    }
    reverse(all(B));

    int ans = 1;
    for(int x = LOG; x >= 0; x--){
        int xo = 0;
        trav(b, B){
            if(b != 0){
                int i = (b-1)%(1 << x)+1;
                xo ^= h(i);
            }
        }

        if(xo == 0){
            ans += (1 << x);
            rep(c1,0,sz(B)){
                B[c1] = max(0, B[c1]-(1 << x));
            }
        }
        else{
            rep(c1,0,sz(B)){
                if(B[c1] != 0)B[c1] = ((B[c1]-1)%(1 << x)+1);
            }
        }
    }
    return ans;
}

int main() { 

    cin >> n;
    rep(c1,0,n){
        int a;
        cin >> a;
        A.push_back(a);
    }
    cout << solve_fast(A) << "\n";

    return 0;
}