#include <bits/stdc++.h>
using namespace std;

// Compute LCS using Hunt–Szymanski + LIS in O(matches * log matches)
string huntSzymanskiLCS(const string& A, const string& B) {
    int n = A.size(), m = B.size();
    array<vector<int>, 256> pos;
    for (int j = 0; j < m; ++j) {
        pos[(unsigned char)B[j]].push_back(j);
    }

    vector<int> seq;
    seq.reserve(n * 2);
    // For each char in A, add matching B-indices in reverse order
    for (char c : A) {
        auto& vec = pos[(unsigned char)c];
        for (auto rit = vec.rbegin(); rit != vec.rend(); ++rit) {
            seq.push_back(*rit);
        }
    }
    int S = seq.size();
    if (S == 0) return "";

    // Arrays for LIS DP + reconstruction
    vector<int> P(S, -1), M(S + 1, -1);
    int L = 0;
    for (int i = 0; i < S; ++i) {
        int lo = 1, hi = L;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (seq[M[mid]] < seq[i]) lo = mid + 1;
            else hi = mid - 1;
        }
        int k = lo;
        P[i] = (k > 1 ? M[k - 1] : -1);
        M[k] = i;
        if (k > L) L = k;
    }

    // Reconstruct LIS (LCS indices)
    vector<int> lis_idx;
    lis_idx.reserve(L);
    for (int idx = M[L]; idx != -1; idx = P[idx]) {
        lis_idx.push_back(seq[idx]);
    }
    reverse(lis_idx.begin(), lis_idx.end());

    // Build LCS string
    string lcs;
    lcs.reserve(L);
    for (int j : lis_idx) lcs.push_back(B[j]);
    return lcs;
}

// Build shortest common supersequence using the LCS
string shortestCommonSupersequence(string& A, string& B, const string& lcs) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    if (!getline(cin, A) || !getline(cin, B)) return 0;
    cout << shortestCommonSupersequence(A, B, huntSzymanskiLCS(A,B)) << '\n';
    return 0;
}
