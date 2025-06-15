#include <x86intrin.h>
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
#define popcnt(x) __popcnt64(x)
#else
#define popcnt(x) __builtin_popcountll(x)
#endif


int LCS(const string& s1, const string& s2) {
    int m = s1.length();
    int n = s2.length();

    // Create a DP table
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp.back().back();
}

int lcsbitslow(const string& s1, const string& s2)
{
    const string& a = sz(s1) > sz(s2) ? s2 : s1;
    const string& b = sz(s1) > sz(s2) ? s1 : s2;

    vi dp(sz(a)+2);
    dp.back() = 1;

    repe(c, b)
    {
        dp.back() = 1;
        int last = sz(dp)-1;
        for (int i = sz(a) - 1; i >= 0; i--)
        {
            if (dp[i+1])
            {
                last = i + 1;
            }
            if (c==a[i])
            {
                dp[last] = 0;
                dp[i+1] = 1;
                last = i + 1;
            }
        }
    }
    dp.back() = 1;

    return accumulate(all(dp),0LL) - 1;
}

const int sigma = 26;
typedef unsigned long long ull;

int lcsfast(const string& s1, const string& s2)
{
    const string& a = sz(s1) > sz(s2) ? s2 : s1;
    const string& b = sz(s1) > sz(s2) ? s1 : s2;

    int numblocks = (sz(a) + 2 + 63) / 64;
    vector<ull> dp(numblocks, numeric_limits<ull>::max());

    auto set = [&](int ind, vector<ull>& arr)
        {
            arr[ind / 64] |= (1ULL << (ind%64));
        };

    vector<ull> occs[26];
    rep(s, 26) occs[s] = vector<ull>(numblocks);
    
    rep(i, sz(a))
    {
        set(i, occs[a[i] - 'a']);
    }

    repe(c, b)
    {
        vector<ull>& occ = occs[c-'a'];

        ull carry = 0;

        rep(i, numblocks)
        {
            ull s;
            carry = __builtin_uaddll_overflow(carry, dp[i], &s) | __builtin_uaddll_overflow(s, (dp[i] & occ[i]), &s);
            dp[i] = (s | (dp[i] & ~occ[i]));
        }
    }
    int ret = 0;
    rep(i, numblocks) ret += popcnt(dp[i]);
    return 64 * numblocks - ret;
}

int lcsfast2(const string& s1, const string& s2)
{
    const string& a = sz(s1) > sz(s2) ? s2 : s1;
    const string& b = sz(s1) > sz(s2) ? s1 : s2;

    int numblocks = (sz(a) + 2 + 63) / 64;
    vector<ull> dp(numblocks, numeric_limits<ull>::max());

    auto set = [&](int ind, vector<ull>& arr)
        {
            arr[ind / 64] |= (1ULL << (ind%64));
        };

    vector<ull> occs[26];
    rep(s, 26) occs[s] = vector<ull>(numblocks);
    
    rep(i, sz(a))
    {
        set(i, occs[a[i] - 'a']);
    }

    for (char c : b)
    {
        vector<ull>& occ = occs[c-'a'];
        
        bool carry = 0;
        rep(i, numblocks)
        {
            ull s;
            carry = _addcarry_u64(carry, dp[i], (dp[i] & occ[i]), &s);
            dp[i] = (s | (dp[i] & ~occ[i]));
        }
    }
    int ret = 0;
    rep(i, numblocks) ret += popcnt(dp[i]);
    return 64 * numblocks - ret;
}

signed main()
{
    fast();

#if 1
    string a, b;
    cin >> a >> b;
    cout << lcsfast2(a, b);
#elif 1
    int n = 100000;
    uniform_int_distribution<int> alpha(0, 25);
    mt19937 rng(10);
    string a(n,'a');
    string b(n,'a');
    rep(i, n) a[i] = alpha(rng) + 'a';
    rep(i, n) b[i] = alpha(rng) + 'a';
    auto start = chrono::high_resolution_clock::now();
    cout << lcsfast(a, b) << "\n";
    cout << "time 1: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << "ms\n";
    start = chrono::high_resolution_clock::now();
    cout << lcsfast2(a, b) << "\n";
    cout << "time 2: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start).count() << "ms\n";

#else
    uniform_int_distribution<int> alpha(0, 25);
    uniform_int_distribution<int> dist(0, 1000);
    mt19937 rng;
    while (true)
    {
        int n = 128;
        int m = 128;

        string a, b;
        rep(i, n) a += string(1, alpha(rng) + 'a');
        rep(i, m) b += string(1, alpha(rng) + 'a');
        int corr = LCS(a, b);
        int maybe = lcsfast2(a, b);
        if (maybe != corr)
        {
            cout << "L";
            assert(0);
        }
    }
#endif


    return 0;
}
