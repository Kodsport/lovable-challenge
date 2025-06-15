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

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vector<p2> vids(n);
    repe(v, vids) cin >> v.first >> v.second;


    while (q--)
    {
        int k;
        cin >> k;

        int ans = inf;
        vi dp(1 << n);
        rep(mask, 1 << n)
        {
            rep(j, n)
            {
                if (mask & (1 << j)) continue;
                int masked = mask | (1 << j);
                dp[masked] = max(dp[masked], dp[mask] * vids[j].first + vids[j].second);
                if (dp[masked] >= k)
                {
                    dp[masked] = k;
                    ans = min(ans, (int)popcount((unsigned long long)masked));
                }
            }
        }
        if (ans == inf) ans = -1;
        cout << ans << " ";
    }


    return 0;
}
