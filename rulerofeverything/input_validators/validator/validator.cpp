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

void run() {
    int n = Int(1, Arg("maxn"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    for (int i = 0; i < n; ++i) {
        Int(1, ll(1e5));
        Space();
        Int(1, ll(1e5));
        Endl();
    }
    SpacedInts(q, 1LL, ll(8e9));
}
