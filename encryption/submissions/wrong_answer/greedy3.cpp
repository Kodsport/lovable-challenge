#include <bits/stdc++.h>
using namespace std;

#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

// A single partial candidate: 
//  - pos is the next index in b we can match at or after,
//  - subseq is the built‑so‑far LCS.
struct Candidate {
    int pos;
    string subseq;
    bool operator<(Candidate const& o) const {
        // sort primarily by longer subseq, then by smaller pos
        if (subseq.size() != o.subseq.size())
            return subseq.size() > o.subseq.size();
        return pos < o.pos;
    }
};

// beam‑search greedy LCS
string beamGreedyLCS(const string& a,
    const string& b,
    int K = 100)    // beam width
{
    int n = b.size();
    // preprocess b → nextPos[i][c] = first j ≥ i with b[j]=c, or n
    vector<array<int, 26>> nextPos(n + 1);
    for (int c = 0; c < 26; c++)
        nextPos[n][c] = n;
    for (int i = n - 1; i >= 0; --i) {
        nextPos[i] = nextPos[i + 1];
        nextPos[i][b[i] - 'a'] = i;
    }

    // start with an “empty” candidate
    vector<Candidate> beam = { {0, ""} };

    for (char ch : a) {
        int c = ch - 'a';
        vector<Candidate> nextBeam = beam;  // allow “skip ch” for all

        // try matching ch on each candidate
        for (auto& cand : beam) {
            if (cand.pos >= n) continue;
            int j = nextPos[cand.pos][c];
            if (j < n) {
                Candidate ext{ j + 1, cand.subseq + ch };
                nextBeam.push_back(move(ext));
            }
        }

        // prune back to top K
        sort(nextBeam.begin(), nextBeam.end());
        if ((int)nextBeam.size() > K)
            nextBeam.resize(K);
        beam.swap(nextBeam);
    }

    // best subsequence is in beam[0]
    return beam.front().subseq;
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

    cout << shortestCommonSupersequence(a, b, beamGreedyLCS(a, b, 1000));
}
