// knows about optimal order argument. O(N^2)
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

    vector<p2> vids(n);
    repe(v, vids) cin >> v.first >> v.second;
    sort(all(vids), [](p2 a, p2 b)
        {
            if (a.first == 1)
            {
                if (b.first != 1) return true;
                return a.second > b.second;
            }
            return (a.second) * (b.first - 1) > b.second * (a.first - 1);
        });

    while (q--)
    {
        int k;
        cin >> k;
        int ans = inf;

        vvi dp(n + 1, vi(n + 1, -1));
        dp[0][0] = 0;

        rep(i, n)
        {
            rep(j, n)
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

        if (ans == inf) ans = -1;
        cout << ans << " ";
    }

    

    return 0;
}
