#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//#define int ll
#define rep(i,hi) for (int i = 0; i < (hi); i++)

const int inf = int(1e14);

string a, b;
int dp[int(1e5 + 5)][500];
int choice[int(1e5 + 5)][500];

int maxoffset = 249;
int best(int i, int j)
{
    if (i >= a.size()) return 0;
    if (j >= b.size()) return 0;
    //cout << i << " " << j << "\n";

    assert(abs(i - j) < maxoffset);
    int& v = dp[i][i - j + 10];
    int& c = choice[i][i - j + 10];
    if (v != -1) return v;

    int ret = -1;
    if (abs(i + 1 - j) < maxoffset)
    {
        int v = best(i + 1, j);
        if (v > ret) ret = v, c = 0;
    }
    if (abs(i - (j + 1)) < maxoffset)
    {
        int v = best(i, j + 1);
        if (v > ret) ret = v, c = 1;
    }

    if (a[i] == b[j])
    {
        int v = 1 + best(i + 1, j + 1);
        if (v > ret) ret = v, c = 2;
    }

    return v = ret;
}

typedef pair<int, int> p2;

string shortestCommonSupersequence(string& A, string& B, string& lcs) {
    string scs;
    scs.reserve(A.size() + B.size());
    int i = 0, j = 0;
    for (char c : lcs) {
        while (i < (int)A.size() && A[i] != c) scs.push_back(A[i++]);
        while (j < (int)B.size() && B[j] != c) scs.push_back(B[j++]);
        scs.push_back(c);
        ++i; ++j;
    }
    if (i < (int)A.size()) scs.append(A, i, string::npos);
    if (j < (int)B.size()) scs.append(B, j, string::npos);
    return scs;
}

signed main()
{
    memset(dp, -1, sizeof(dp));
    memset(choice, -1, sizeof(choice));
    cin >> a >> b;

    int lcs_len = best(0, 0);

    string ans = "";
    p2 state = p2(0, 0);

    while (choice[state.first][state.first - state.second + 10] != -1)
    {
        int i, j;
        tie(i, j) = state;
        if (choice[i][i - j + 10] == 0) i++;
        else if (choice[i][i - j + 10] == 1) j++;
        else if (choice[i][i - j + 10] == 2) ans += a[i], j++, i++;

        state = p2(i, j);
    }
    cerr << lcs_len << "\n";
    cout << shortestCommonSupersequence(a, b, ans);
}
