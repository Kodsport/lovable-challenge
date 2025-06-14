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
    sort(all(vids), [](p2 a, p2 b)
        {
            return (a.second) * (b.first - 1) > b.second * (a.first - 1);
        });

    int maxt = int(8e9) + 10;
    int p = 1;
    repe(v, vids)
    {
        p *= v.first;
        if (p > maxt) break;
    }
    if (p > maxt)
    {
        // ans is small

        vvi dp(sz(vids) + sz(ones) + 1, vi(40, 0));

        rep(i, sz(ones))
        {
            rep(j, 39)
            {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                dp[i + 1][j] = min(dp[i + 1][j], maxt);
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] + ones[i]);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], maxt);
            }
        }
        repp(i, sz(ones), sz(ones) + sz(vids))
        {
            rep(j, 39)
            {
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                dp[i + 1][j] = min(dp[i + 1][j], maxt);
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * vids[i - sz(ones)].first + vids[i - sz(ones)].second);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], maxt);
            }
        }


        while (q--)
        {
            int t;
            cin >> t;
            int ans = inf;

            rep(j, 40)
            {
                if (dp.back()[j] >= t)
                {
                    ans = min(ans, j);
                }
            }

            if (ans == inf) ans = -1;
            cout << ans << ' ';
        }
    }
    else
    {

        auto tryv = [&](int start, int k)
            {
                vvi dp(sz(vids) + 1, vi(40, -1));
                rep(i, sz(vids) + 1) rep(j, 39) dp[i][j] = -1;
                dp[0][0] = start;

                rep(i, sz(vids))
                {
                    rep(j, 39)
                    {
                        if (dp[i][j] == -1) continue;
                        dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                        dp[i + 1][j] = min(dp[i + 1][j], k + 1);
                        dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * vids[i].first + vids[i].second);
                        dp[i + 1][j + 1] = min(dp[i + 1][j + 1], k + 1);
                    }
                }
                int ret = inf;
                rep(i, sz(vids) + 1)
                {
                    rep(j, 40)
                    {
                        if (dp[i][j] == -1) continue;
                        if (dp[i][j] >= k)
                        {
                            ret = min(ret, j);
                        }
                    }
                }
                return ret;
            };

        vi pref(ones);
        repp(i, 1, sz(pref)) pref[i] += pref[i - 1];
        pref.insert(begin(pref), 0);
        auto getvpref = [&](int ind, int k)
            {
                int s = pref[ind];
                return tryv(s, k);
            };

        while (q--)
        {
            int k;
            cin >> k;
            int lo = -1;
            int hi = sz(ones) + 1;
            while (lo + 1 < hi)
            {
                int mid = (lo + hi) / 2;
                if (getvpref(mid, k) != inf)
                {
                    hi = mid;
                }
                else lo = mid;
            }

            if (hi == sz(ones) + 1)
            {
                cout << "-1 ";
                continue;
            }
            else
            {
                int ans = hi + getvpref(hi, k);
                repp(i, hi + 1, sz(ones) + 1)
                {
                    if (i >= ans) break;
                    ans = min(ans, i + getvpref(i, k));
                }
                cout << ans << " ";
            }
        }
    }

    return 0;
}
