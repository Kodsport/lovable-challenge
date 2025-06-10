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

// Greedy that takes two non-N mugs as long as possible. If there is only one,
// it must be an S, and the answer is 5 (unless n=2).

// Should only get the first subtask.

int n;
vi F(4,0);

int ctn(char ch){
    if(ch == 'N')return 0;
    if(ch == 'W')return 1;
    if(ch == 'S')return 2;
    if(ch == 'E')return 3;
    return -1;
}

int greedy(vi f){
    int d = 0;
    while(1){
        vi nz;
        rep(c1,1,4){
            int i = 0;
            while(i < f[c1] && sz(nz) < 2){
                nz.push_back(c1);
                i++;
            }
        }
        if(sz(nz) == 0)return d;
        if(sz(nz) == 1)return d+5;
        f[nz[0]]--;
        f[nz[1]]--;
        f[(nz[0]+1)%4]++;
        f[(nz[1]+1)%4]++;
        d++;
    }
}

int main() { 

    cin >> n;
    string s;
    cin >> s;
    trav(ch, s){
        F[ctn(ch)]++;
    }

    if(n == 2){
        if(s[0] == s[1]){
            cout << (4-ctn(s[0]))%4 << "\n";
        }
        else{
            cout << "-1\n";
        }
        return 0;
    }

    int sum = 0;
    rep(c1,0,4){
        sum += c1*F[c1];
    }

    if(sum%2 == 1){
        cout << "-1\n";
        return 0;
    }

    cout << greedy(F) << "\n";

    return 0;
}