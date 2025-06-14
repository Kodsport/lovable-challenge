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

void run() {
    int N = Int(1, Arg("MAXN", MAXN));
    Endl();
    string s = Line();

    for (auto &ch: s) assert('a' <= ch and ch <= 'z');

    assert(sz(s) == N);

    Eof();
}

