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

vi bestat(40);
int t;

void rec(int i, int taken, int subs, vi& used, vector<p2>& vids)
{
    bestat[taken] = max(bestat[taken], subs);
    if (subs>=t)
    {
        return;
    }
    if (i == sz(vids)) return;

    int ans = inf;
    rep(i, sz(vids))
    {
        if (used[i]) continue;
        used[i] = 1;
        rec(i + 1, taken + 1, subs * vids[i].first + vids[i].second, used, vids);
        used[i] = 0;
    }
}

signed main()
{
    fast();

    int n;
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

    vi used(sz(vids));
    rec(0, 0, 0, used, vids);
    int ans = inf;

    rep(i, 40)
    {
        if (bestat[i]>=t)
        {
            ans = min(ans, i);
            continue;
        }
        int s = 0;
        rep(j, sz(ones))
        {
            s += ones[j];
            if (bestat[i]+s>=t)
            {
                ans = min(ans, j + 1 + i);
                break;
            }
        }
    }

    if (ans == inf)
    {
        cout << "-1";
    }
    else cout << ans;

    return 0;
}
