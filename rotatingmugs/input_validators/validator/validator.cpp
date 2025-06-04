#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 500000;
const int MAXS = 1000000000;

void run() {
    int n = Int(1, Arg("maxn", MAXN));
    int maxs = int(Arg("maxs", MAXS));
    Endl();
    vi s = SpacedInts(n, 1, maxs);
    set<int> S;
    trav(x, s){
        S.insert(x);
    }
    assert(sz(S) == n);

    Eof();
}

