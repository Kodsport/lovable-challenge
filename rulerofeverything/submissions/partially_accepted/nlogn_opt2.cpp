#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
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

    vi dp(40, -1);

    auto tryv = [&](int start, int k)
        {
            rep(j, 40) dp[j] = 0;
            dp[0] = start;

            rep(i, sz(vids))
            {
                for (int j = 39; j > 0; j--)
                {
                    dp[j] = max(dp[j], dp[j - 1] * vids[i].first + vids[i].second);
                }
                rep(j, 39) dp[j] = min(dp[j], k + 1);
            }

            rep(i, 40)
            {
                if (dp[i] >= k) return i;
            }

            return inf;
        };


    auto getvpref = [&](int ind, int k)
        {
            int s = 0;
            rep(i, ind) s += ones[i];
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
    cout << "\n";

    return 0;
}
