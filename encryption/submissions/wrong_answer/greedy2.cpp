#include <bits/stdc++.h>
using namespace std;


// The basic greedy scan (from the earlier snippet)
string greedyScan(const string& a, const string& b) {
    int n = b.size();
    vector<array<int,26>> nextPos(n+1);
    for(int c = 0; c < 26; c++) 
        nextPos[n][c] = n;
    for(int i = n-1; i >= 0; i--) {
        nextPos[i] = nextPos[i+1];
        nextPos[i][b[i]-'a'] = i;
    }

    string res;
    int pos = 0;
    for(char ch : a) {
        int nxt = nextPos[pos][ch-'a'];
        if(nxt < n) {
            res.push_back(ch);
            pos = nxt + 1;
        }
    }
    return res;
}

// A “smarter greedy” that takes the better of forward vs. reverse
string smarterGreedyLCS(const string& a, const string& b) {
    // 1) forward greedy
    string fwd = greedyScan(a, b);

    // 2) backward greedy: reverse both strings, run greedy, then reverse result
    string ra = a; reverse(ra.begin(), ra.end());
    string rb = b; reverse(rb.begin(), rb.end());
    string revMatch = greedyScan(ra, rb);
    reverse(revMatch.begin(), revMatch.end());

    // 3) pick whichever is longer
    return (revMatch.size() > fwd.size() ? revMatch : fwd);
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

    cout << shortestCommonSupersequence(a, b, smarterGreedyLCS(a, b));

}