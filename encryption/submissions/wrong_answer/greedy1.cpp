#include <bits/stdc++.h>
using namespace std;


// Returns a common subsequence of a and b by greedily
// matching each character of a to its next occurrence in b.
// Time: O(|a| + |b| + 26*|b|)  Space: O(|b|*26)
string greedyLCS(const string& a, const string& b) {
    int n = b.size();
    // nextPos[i][c] = the smallest index >= i where b[index] == c,
    // or n if none.
    vector<array<int,26>> nextPos(n+1);
    // Initialize the “beyond end” row to n (sentinel)
    for(int c = 0; c < 26; c++) 
        nextPos[n][c] = n;
    // Build table bottom-up
    for(int i = n-1; i >= 0; i--) {
        // copy from row i+1
        nextPos[i] = nextPos[i+1];
        // update the char at b[i]
        nextPos[i][b[i]-'a'] = i;
    }

    string result;
    int posInB = 0;
    // For each char in a, see if we can match it in b at or after posInB
    for(char ch : a) {
        int c = ch - 'a';
        if (posInB > n) break;            // no more matches possible
        int nxt = nextPos[posInB][c];
        if (nxt < n) {
            result.push_back(ch);
            posInB = nxt + 1;
        }
    }
    return result;
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

    cout << shortestCommonSupersequence(a, b, greedyLCS(a, b));

}