#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

int main()
{
    fast();

    string a, b, _;
    cin >> a >> b >> _;

    int n = sz(a), m = sz(b);

    vvi memo(n + 1, vi(m + 1, n+m+5));
    vvi choice(n + 1, vi(m + 1, -1));

    memo[n][m] = 0;

    for (int i = n; i >= 0; i--) {
        for (int j = m; j >= 0; j--) {
            if (i < n && j < m && a[i] == b[j]) {
                if (1 + memo[i + 1][j + 1] < memo[i][j]) {
                    memo[i][j] = 1 + memo[i + 1][j + 1];
                    choice[i][j] = 0;
                }
            }
            if (i < n) {
                if (1 + memo[i + 1][j] < memo[i][j]) {
                    memo[i][j] = 1 + memo[i + 1][j];
                    choice[i][j] = 1;
                }
            }
            if (j < m) {
                if (1 + memo[i][j + 1] < memo[i][j]) {
                    memo[i][j] = 1 + memo[i][j + 1];
                    choice[i][j] = 2;
                }
            }
        }
    }

    p2 state = p2(0, 0);
    string ans = "";
    while (state != p2(n, m))
    {
        if (choice[state.first][state.second] == 0)
        {
            ans += a[state.first];
            state.first++;
            state.second++;
        }
        else if (choice[state.first][state.second] == 1)
        {
            ans += a[state.first];
            state.first++;
        }
        else
        {
            ans += b[state.second];
            state.second++;
        }
    }

    cout << ans << '\n';

    return 0;
}
