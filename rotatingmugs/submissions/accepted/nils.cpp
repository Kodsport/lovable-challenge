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

int dist(vi f){
    int d = 0;
    rep(c1,0,4){
        d += f[c1] * ((4-c1)%4);
    }
    return d/2;
}

ll has(vi f){
    ll x = 0;
    trav(y, f){
        x *= 1234567;
        x += y;
    }
    return x;
}

vector<vi> neighbours(vi f){
    vector<vi> res;
    rep(c1,0,4){
        rep(c2,c1,4){
            if(f[c1] > 0 && f[c2] > 0 && (c1 != c2 || f[c1] > 1)){
                vi f2 = f;
                f2[c1]--;
                f2[c2]--;
                f2[(c1+1)%4]++;
                f2[(c2+1)%4]++;
                res.push_back(f2);
            }
        }
    }
    return res;
}

set<ll> seen;
map<ll,int> M;

int astar(vi f){
    queue<vi> Q;
    ll h = has(f);
    M[h] = 0;
    int g = greedy(f);
    Q.push(f);

    while(!Q.empty()){
        vi f1 = Q.front();
        Q.pop();
        h = has(f1);
        
        if(seen.find(h) == seen.end()){
            seen.insert(h);
            vector<vi> NB = neighbours(f1);
            
            trav(f2, NB){
                ll h2 = has(f2);
                if(M.find(h2) == M.end()){
                    int d1 = M[h];
                    int dst = dist(f2);

                    if(d1+1+dst < g){
                        M[h2] = d1+1;
                        if(dst == 0)return d1+1;
                        Q.push(f2);
                    }
                }
                
            }
            
        }
        
    }

    return g;
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

    cout << astar(F) << "\n";

    return 0;
}