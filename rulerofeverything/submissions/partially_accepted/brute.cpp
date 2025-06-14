// do recursive bruteforce on those with a > 1. bounded by n!/(n-logn)!
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int t;
int best = inf;

void rec(int taken, int subs, vi& used, vector<p2>& vids)
{
    if (taken >= best) return;
    if (subs >= t)
    {
        best = taken;
        return;
    }

    int ans = inf;
    rep(i, sz(vids))
    {
        if (used[i]) continue;
        used[i] = 1;
        rec(taken + 1, subs * vids[i].first + vids[i].second, used, vids);
        used[i] = 0;
    }
}

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;

    vi ones;

    vector<p2> vids;
    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        if (a == 1) ones.push_back(b);
        else vids.emplace_back(a, b);
    }
    sort(all(ones));
    reverse(all(ones));

    while (q--)
    {
        cin >> t;
        int ans = inf;

        auto cost = [&](int start)
            {
                best = inf;
                vi used(sz(vids));

                rec(0, start, used, vids);
                return best;
            };

        ans = min(ans, cost(0));
        int p = 0;
        rep(i, sz(ones))
        {
            p += ones[i];
            if (i + 1 >= ans) continue;
            ans = min(ans, i + 1 + cost(p));
        }

        if (ans == inf) ans = -1;
        cout << ans << " ";
    }
    cout << '\n';
    

    return 0;
}
