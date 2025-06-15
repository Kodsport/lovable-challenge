#include <bits/stdc++.h>
using namespace std;

// Node for reconstructing the subsequence
struct Node {
    char c;
    Node* prev;
    Node(char c_, Node* p_) : c(c_), prev(p_) {}
};

// Returns the LCS string of a and b in O(|a| * L) time (alphabet = lowercase ASCII).
string lcs_aL(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    const int ALPHA = 26;
    const int INF = m + 1;

    // 1) Build next-pos table for b: next_pos[j][c] = smallest k > j with b[k]==c, or INF.
    vector<array<int, ALPHA>> next_pos(m + 2);
    // Initialize row m (and m+1) to INF
    for (int c = 0; c < ALPHA; ++c) {
        next_pos[m][c] = next_pos[m + 1][c] = INF;
    }
    // Fill backwards
    for (int j = m - 1; j >= 0; --j) {
        next_pos[j] = next_pos[j + 1];
        next_pos[j][b[j] - 'a'] = j;
    }

    // 2) dp[k] = smallest index in b where some common subsequence of length k ends
    vector<int> dp(m + 2, INF);
    dp[0] = -1;

    // head[k] will point to the last Node of a length-k subsequence
    vector<Node*> head(m + 2, nullptr);

    int maxL = 0;
    for (int i = 0; i < n; ++i) {
        // go backwards so updates to dp[k+1] don't affect smaller k in this i-iteration
        for (int k = maxL; k >= 0; --k) {
            int j = dp[k];
            if (j < m) {
                int nj = next_pos[j + 1][a[i] - 'a'];
                if (nj < dp[k + 1]) {
                    dp[k + 1] = nj;
                    // link a[i] onto the k‑length chain
                    head[k + 1] = new Node(a[i], head[k]);
                    maxL = max(maxL, k + 1);
                }
            }
        }
    }

    // 3) Reconstruct the sequence from head[maxL]
    string lcs;
    Node* cur = head[maxL];
    while (cur) {
        lcs.push_back(cur->c);
        cur = cur->prev;
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}


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


signed main()
{
    string a, b;
    cin >> a >> b;

    cout << shortestCommonSupersequence(a, b, lcs_aL(a, b));

}