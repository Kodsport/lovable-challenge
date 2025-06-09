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

const int MAXM = 500000;

void run() {
    int m = Int(2, Arg("MAXM", MAXM));
    Endl();
    string a = Line();


    for (auto &ch:a) assert(ch == 'N' or ch == 'W' or ch == 'E' or ch == 'S');
    
    bool onlytwo = Arg("onlytwo", 0);
    if (onlytwo) for (auto &ch:a) assert(ch == 'N' or ch == 'E');

    assert(sz(a) == m);

    Eof();
}

