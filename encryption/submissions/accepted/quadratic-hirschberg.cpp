#include <bits/stdc++.h>
using namespace std;

// Compute the LCS “score” row of A vs. B in O(n·m) time and O(m) space.
// If revA or revB is true, traverse A or B in reverse.
vector<int> lcsScore(const string& A, const string& B, bool revA=false, bool revB=false) {
    int n = A.size(), m = B.size();
    vector<int> dp(m+1, 0), prev(m+1, 0);

    for(int i = 0; i < n; i++){
        // choose A[i] either from front or back
        char a_char = revA ? A[n-1-i] : A[i];
        swap(dp, prev);
        for(int j = 0; j < m; j++){
            char b_char = revB ? B[m-1-j] : B[j];
            if(a_char == b_char)
                dp[j+1] = prev[j] + 1;
            else
                dp[j+1] = max(dp[j], prev[j+1]);
        }
    }
    return dp;
}

// Hirschberg’s divide‑and‑conquer LCS: returns the actual LCS string of A and B.
string hirschbergLCS(const string& A, const string& B){
    int n = A.size(), m = B.size();
    if(n == 0 || m == 0) {
        return "";
    }
    if(n == 1){
        // Base case: A is length 1
        for(char c : B)
            if(c == A[0])
                return string(1, c);
        return "";
    }
    // Divide A in half
    int i = n/2;
    // Forward LCS scores for A[0..i) vs. B
    vector<int> scoreL = lcsScore(string(A.begin(), A.begin()+i), B, false, false);
    // Backward LCS scores for A[i..n) vs. B, both reversed
    vector<int> scoreR = lcsScore(string(A.begin()+i, A.end()), B, true, true);

    // Find split point k in B maximizing scoreL[k] + scoreR[m-k]
    int k = 0, best = -1;
    for(int j = 0; j <= m; j++){
        int val = scoreL[j] + scoreR[m-j];
        if(val > best){
            best = val;
            k = j;
        }
    }

    // Recurse on the two halves
    string leftLCS  = hirschbergLCS(string(A.begin(), A.begin()+i),
                                    string(B.begin(), B.begin()+k));
    string rightLCS = hirschbergLCS(string(A.begin()+i, A.end()),
                                    string(B.begin()+k, B.end()));
    return leftLCS + rightLCS;
}

// Build the shortest common supersequence of A and B by merging around their LCS.
string shortestCommonSupersequence(const string& A, const string& B) {
    string L = hirschbergLCS(A, B);
    string scs;
    int i = 0, j = 0;
    // For each character c in LCS, append the unmatched parts of A and B first
    for(char c : L) {
        while(A[i] != c) scs += A[i++];
        while(B[j] != c) scs += B[j++];
        // then append the common char
        scs += c;
        i++; j++;
    }
    // append any leftovers
    scs += A.substr(i);
    scs += B.substr(j);
    return scs;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b, dummy;
    // input: two strings and (ignored) third token
    cin >> a >> b >> dummy;

    cout << shortestCommonSupersequence(a, b) << "\n";
    return 0;
}
