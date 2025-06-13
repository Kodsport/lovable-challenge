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

const int MAXN = 300000;

void run() {
    int MAXA = Arg("MAXA", 1e9);
    int N = Int(1, Arg("MAXN", MAXN));
    Endl();
    vi a = SpacedInts(N, 1, MAXA);

    Eof();
}

