// INCORRECT
// knows about optimal order argument. O(NlogN) by only caring about states with at most 40
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

    while (q--)
    {
        int k;
        cin >> k;
        int ans = inf;

        vvi dp(sz(vids) + 1, vi(40, -1));
        dp[0][0] = 0;

        rep(i, sz(vids))
        {
            rep(j, 38)
            {
                if (dp[i][j] == -1) continue;
                if (dp[i][j] >= k)
                {
                    ans = min(ans, j);
                }
                dp[i + 1][j] = max(dp[i + 1][j], dp[i][j]);
                dp[i + 1][j] = min(dp[i + 1][j], k + 1);
                dp[i + 1][j + 1] = max(dp[i + 1][j + 1], dp[i][j] * vids[i].first + vids[i].second);
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], k + 1);

            }
        }

        vi bestat(40);
        rep(i, sz(vids) + 1)rep(j, 40) bestat[j] = max(bestat[j], dp[i][j]);
        rep(i, 40)
        {
            if (bestat[i] >= k)
            {
                ans = min(ans, i);
                continue;
            }
            int s = 0;
            rep(j, sz(ones))
            {
                s += ones[j];
                if (bestat[i] + s >= k)
                {
                    ans = min(ans, j + 1 + i);
                    break;
                }
            }
        }

        if (ans == inf) ans = -1;
        cout << ans << " ";
    }


    return 0;
}
