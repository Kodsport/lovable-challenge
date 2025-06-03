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

const ll nils = 1000000007;
const ll LOG = 30;
int n;
vi A;


const int MAXS = 1000001;

int TWOS[MAXS] = {0};

int twos(int x){
    if(TWOS[x] != 0)return TWOS[x];
    int res = 0;
    int t = 2;
    while(t <= x){
        res += x / t;
        t *= 2;
    }
    TWOS[x] = res;
    return res;
}

int bin(int x, int y){
    if(x < y || x < 0 || y < 0)return 0;
    int t1 = twos(x);
    int t2 = twos(x-y);
    int t3 = twos(y);
    if(t1 == t2+t3)return 1;
    return 0;
}

int solve(vi &A){
    int t = 0;
    while(1){
        int p = 0;
        trav(a, A){
            p ^= bin(a, t);
        }
        if(p == 1)return t+1;
        t++;
    }
}

int main() { 

    cin >> n;
    rep(c1,0,n){
        int a;
        cin >> a;
        A.push_back(a);
    }
    cout << solve(A) << "\n";

    return 0;
}