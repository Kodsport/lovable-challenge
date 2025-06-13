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


signed main()
{
    fast();

    int n, t;
    cin >> n >> t;

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
    sort(all(vids), [](p2 a, p2 b)
        {
            return (a.second) * (b.first - 1) > b.second * (a.first - 1);
        });

    vvi dp(sz(vids) + 1, vi(40, -1));

    auto tryv = [&](int start)
        {
            rep(i, sz(vids)+1) rep(j, 39) dp[i][j] = -1;
            dp[0][0] = start;

            rep(i, sz(vids))
            {
                rep(j, 39)
                {
                    if (dp[i][j] == -1) continue;
                    dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                    dp[i + 1][j] = min(dp[i + 1][j], t + 1);
                    dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * vids[i].first + vids[i].second);
                    dp[i + 1][j + 1] = min(dp[i + 1][j + 1], t + 1);
                }
            }
            int ret = inf;
            rep(i, sz(vids) + 1)
            {
                rep(j, 40)
                {
                    if (dp[i][j] == -1) continue;
                    if (dp[i][j] >= t)
                    {
                        ret = min(ret, j);
                    }
                }
            }
            return ret;
        };


    auto getvpref = [&](int ind)
        {
            int s = 0;
            rep(i, ind) s += ones[i];
            return tryv(s);
        };

    int lo = -1;
    int hi = sz(ones) + 1;
    while (lo+1<hi)
    {
        int mid = (lo + hi) / 2;
        if (getvpref(mid) != inf)
        {
            hi = mid;
        }
        else lo = mid;
    }

    if (hi==sz(ones) + 1)
    {
        cout << "-1\n";
        return 0;
    }
    else
    {
        int ans = hi + getvpref(hi);
        repp(i, hi + 1, sz(ones)+1)
        {
            if (i >= ans) break;
            ans = min(ans, i+getvpref(i));
        }
        cout << ans << "\n";
    }

    return 0;
}
