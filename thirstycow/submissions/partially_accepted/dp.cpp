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

map<p2, int> dp;

int best(int i, int sub, vi& nums)
{
    if (i == sz(nums)) return 0;
    p2 state = p2(i, sub);
    if (dp.count(state)) return dp[state];

    int ret = 0;
    

    if (nums[i] - sub >= 0) ret = max(ret, nums[i] - sub + best(i + 1, sub + (nums[i] - sub), nums));
    ret = max(ret, best(i + 1, sub, nums));

    return dp[state] = ret;
}

signed main()
{
    fast();

    int n;
    cin >> n;
    vi nums(n);
    repe(v, nums) cin >> v;

    cout << best(0,0,nums);

    return 0;
}