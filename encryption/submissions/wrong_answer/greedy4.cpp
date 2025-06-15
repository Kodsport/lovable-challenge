#include <bits/stdc++.h>
using namespace std;

#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;


// Returns *a* common subsequence (not guaranteed optimal in worst‐case),
// but in practice very close to LCS on real data, in O((|s₁| + |s₂|) log |s₂|).
string heuristic_lcs(const string &s1, const string &s2) {
    // 1) Build for s2: for each character c, a sorted list of all indices i where s2[i] == c.
    vector<vector<int>> pos(256);
    for(int i = 0; i < (int)s2.size(); i++)
        pos[(unsigned char)s2[i]].push_back(i);

    // 2) Now scan s1, greedily pick the earliest possible match in s2 after the last one.
    string res;
    res.reserve(min(s1.size(), s2.size()));
    int last = -1;
    for(char c : s1) {
        auto &vec = pos[(unsigned char)c];
        // find the first occurrence > last
        auto it = upper_bound(vec.begin(), vec.end(), last);
        if(it == vec.end()) continue;
        last = *it;
        res.push_back(c);
    }
    return res;
}


string shortestCommonSupersequence(string& A, string& B, const string& lcs) {
    cerr << "lcs length:" << lcs.size() << "\n";
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
    string a, b;
    cin >> a >> b;

    cout << shortestCommonSupersequence(a, b, heuristic_lcs(a, b));

}