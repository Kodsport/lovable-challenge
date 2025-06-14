// do recursive bruteforce on those with a > 1. 
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

int best = inf;
int t;

void rec(int taken, int subs, map<int, int>& groupind, map<int, vi>& vids)
{
    if (taken >= best) return;
    if (subs >= t)
    {
        best = taken;
        return;
    }

    for (auto vid : vids)
    {
        if (groupind[vid.first] == sz(vid.second)) continue;
        groupind[vid.first]++;
        rec(taken + 1, subs * vid.first + vid.second[groupind[vid.first] - 1], groupind, vids);
        groupind[vid.first]--;
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

    map<int, vi> groups;
    for (auto& v : vids)
    {
        groups[v.first].push_back(v.second);
    }
    map<int, int> groupind;
    for (auto& g : groups)
    {
        groupind[g.first] = 0;
        sort(all(g.second));
        reverse(all(g.second));
    }

    auto tryv = [&](int start)
        {
            best = inf;
            rec(0, start, groupind, groups);
            return best;
        };

    while (q--)
    {
        cin >> t;
        int ans = inf;

        ans = min(ans, tryv(0));
        int s = 0;
        rep(numtake, sz(ones))
        {
            s += ones[numtake];
            ans = min(ans, numtake + 1 + tryv(s));
        }


        if (ans == inf) ans = -1;
        cout << ans << " ";
    }
    cout << '\n';

    return 0;
}
