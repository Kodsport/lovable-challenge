#include <bits/stdc++.h>
using namespace std;

#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

static string greedy(const string &A, const string &B) {
    vector<vector<int>> pos(256);
    for (int i = 0; i < (int)B.size(); i++)
        pos[(unsigned char)B[i]].push_back(i);
    string R;
    R.reserve(min(A.size(), B.size()));
    int last = -1;
    for (char c : A) {
        auto &v = pos[(unsigned char)c];
        auto it = upper_bound(v.begin(), v.end(), last);
        if (it != v.end()) {
            last = *it;
            R.push_back(c);
        }
    }
    return R;
}

// run greedy in four “directions” and pick the best
string improved_greedy_lcs(const string &A, const string &B) {
    string best;

    // 1) forward A→B
    best = greedy(A, B);

    // 2) forward B→A, then reverse result
    {
        string t = greedy(B, A);
        reverse(t.begin(), t.end());
        if (t.size() > best.size()) best = move(t);
    }

    // 3) backward (rev A)→(rev B), then reverse
    {
        string Ar(A.rbegin(), A.rend()), Br(B.rbegin(), B.rend());
        string t = greedy(Ar, Br);
        reverse(t.begin(), t.end());
        if (t.size() > best.size()) best = move(t);
    }

    // 4) backward B→A on reversed, then reverse
    {
        string Ar(A.rbegin(), A.rend()), Br(B.rbegin(), B.rend());
        string t = greedy(Br, Ar);
        reverse(t.begin(), t.end());
        if (t.size() > best.size()) best = move(t);
    }

    return best;
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

    cout << shortestCommonSupersequence(a, b, improved_greedy_lcs(a, b));

}