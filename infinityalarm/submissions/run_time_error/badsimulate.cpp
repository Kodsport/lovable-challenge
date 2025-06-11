// @EXPECTED_GRADES@ RTE TLE RTE
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a+b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

    int n;
    cin >> n;

    Tree seg(7e5);

    vi array;

    vector<pii> remove;

    rep(i,0,n) {
        int temp;
        cin >> temp;
        array.push_back(temp);
        seg.update(temp,1);
        remove.push_back({temp,temp+1});
    }

    sort(all(array));
    if (sz(array) == 2) {
        if (__builtin_popcount(array[1]-array[0]) == 1) {
            cout << array[1]-array[0]+1 << "\n";
            return 0;
        }
    }

    int out = 0;
    while (seg.query(0,7e5)%2 == 0) {
        ll tot = seg.query(0,7e5);

        ll prev = 0;
        vector<pii> toadd;
        rep(cur,1,tot+1) {
            ll lo = 0;
            ll hi = 7e5-1;

            while (lo < hi) {
                ll mid = (lo+hi)/2;
                if (seg.query(0,mid+1) >= cur) {
                    hi = mid;
                }
                else {
                    lo = mid +1;
                }
            }

            if (cur%2 == 0) {
                toadd.push_back({prev+1,lo+1});
            }
            prev = lo;
        }

        for (auto &[x,y]:remove) {
            rep(i,x,y) {
                seg.update(i,0);
            }
        }
        remove.clear();
            
        for (auto &[x,y]:toadd) {
            rep(i,x,y) {
                seg.update(i,1);
            }
            remove.push_back({x,y});

        }
        out++;

    }

    cout << out+1 << "\n";
}