#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <immintrin.h>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)1e18;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define sz(x) ((int)(x.size()))

const ll maxt = ll(8e9)+10;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> ones;
    vector<pair<ll, ll>> vids;
    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        if (a == 1) ones.push_back(b);
        else vids.emplace_back(a, b);
    }

    // sort by your optimal-order comparator
    sort(vids.begin(), vids.end(), [&](auto& A, auto& B) {
        // same as: A.second*B.first + B.second   >   B.second*A.first + A.second
        return A.second * B.first + B.second
             > B.second * A.first + A.second;
        });

    vector<ll> dp(n + 1, 0);

    rep(i, sz(ones))
    {
        for (int j = n; j > 0; j--)
        {
            dp[j] = max(dp[j], dp[j-1] + ones[i]);
        }
        rep(j, n+1) dp[j] = min(dp[j], maxt);
    }
    rep(i, sz(vids))
    {
        for (int j = n; j > 0; j--)
        {
            dp[j] = max(dp[j], dp[j - 1] * vids[i].first + vids[i].second);
        }
        rep(j, n+1) dp[j] = min(dp[j], maxt);
    }

    while (q--)
    {
        ll k;
        cin >> k;

        // find the smallest j such that dp[j] >= t
        int ans = -1;
        for (int j = 0; j <= n; j++) {
            if (dp[j] >= k) {
                ans = j;
                break;
            }
        }

        cout << ans << " ";
    }
    cout << '\n';

    return 0;
}
