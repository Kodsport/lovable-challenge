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
    int maxn = Arg("maxn");

    auto check = [maxn](int minlen)
    {
        string l = Line();
        assert(sz(l)>=minlen && sz(l) <= maxn);
        for (char c : l) assert(c>='a'&&c<='z');
    };

    check(1);
    check(1);
    check(0);
}
