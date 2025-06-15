#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int inf = int(1e14);

string a, b;
// dp[i][offset] where offset = i - j + maxoffset_val
// The maximum possible value for i - j is when i = N-1 and j = 0, so N-1.
// The minimum possible value for i - j is when i = 0 and j = M-1, so -(M-1).
// maxoffset_val should be chosen such that i - j + maxoffset_val is always non-negative.
// If maxoffset is 249, then the range of i-j is roughly [-248, 248]. So, maxoffset_val = 248 is good.
// The size of the second dimension will be 2 * maxoffset - 1 (or 2 * (maxoffset_val) + 1).
// Let's use 2 * maxoffset for safety, or even better, 2 * maxoffset + 10 as in the original code.
// The original code uses maxoffset = 249, and offset of +10, so the second dimension is effectively sized for range [-249+10, 249+10] after adjustment.
// Let's stick to the original offset strategy.
// dp[i][i - j + 249]
int dp[int(1e5 + 5)][500]; // 500 should be sufficient for 2*249+1. 249 is maxoffset
int choice[int(1e5 + 5)][500];

int maxoffset_val = 249; // This corresponds to the half-width of the band

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> a >> b;

    int N = a.size();
    int M = b.size();

    // Initialize dp table. For LCS, 0 is a valid length. -1 was for memoization.
    // Here, we can initialize with 0, as base cases return 0.
    // The dp table naturally handles out-of-bounds as 0 length LCS.
    // memset(dp, 0, sizeof(dp)); // Not strictly necessary if we iterate from N, M down to 0
    // memset(choice, -1, sizeof(choice)); // choice is still useful for reconstruction

    // Iterate backwards
    for (int i = N; i >= 0; --i) {
        for (int j = M; j >= 0; --j) {
            // Base cases: if either string is exhausted, LCS is 0
            if (i == N || j == M) {
                dp[i][i - j + maxoffset_val] = 0;
                // choice remains -1 or some sentinel for base case, or we don't care.
                continue;
            }

            // Apply the banded DP constraint: only calculate if abs(i - j) < maxoffset_val
            if (abs(i - j) >= maxoffset_val) {
                // We can set dp to a sentinel value or skip. Given the original code,
                // it implies that states outside the band are effectively unreachable or result in a -1.
                // For bottom-up, if we don't calculate, it means it stays at 0 (if initialized to 0),
                // which might be fine for LCS if it's implicitly part of the problem.
                // However, to mimic the original behavior of `best` not returning -1 if outside,
                // we should consider values from within the band.
                // For a proper bottom-up, ensure states are computed or correctly represent the base cases.
                // In LCS, usually if a state is invalid, it means 0 contribution.
                // Let's ensure a valid initialization if we skip.
                dp[i][i - j + maxoffset_val] = 0; // Or some sentinel value if 0 is a possible result for empty strings.
                                                 // Since 0 is a valid LCS length, this is fine.
                continue;
            }

            int current_offset = i - j + maxoffset_val;
            int ret = 0; // Initialize with 0 for LCS length

            // Case 0: Skip a from a (i+1, j)
            // Check if (i+1, j) is within bounds and within the band
            if (i + 1 <= N) { // (i+1, j)
                if (abs((i + 1) - j) < maxoffset_val) {
                    int v = dp[i + 1][(i + 1) - j + maxoffset_val];
                    if (v > ret) ret = v, choice[i][current_offset] = 0;
                } else {
                    // If out of band, it contributes 0 to LCS.
                    // This is implicitly handled if dp is initialized to 0 or
                    // if the best option is always selected (which is 0 from out-of-band).
                }
            }

            // Case 1: Skip b from b (i, j+1)
            // Check if (i, j+1) is within bounds and within the band
            if (j + 1 <= M) { // (i, j+1)
                if (abs(i - (j + 1)) < maxoffset_val) {
                    int v = dp[i][i - (j + 1) + maxoffset_val];
                    if (v > ret) ret = v, choice[i][current_offset] = 1;
                } else {
                    // Similar to above, implicitly 0.
                }
            }

            // Case 2: Match (a[i] == b[j]) (i+1, j+1)
            // Check if (i+1, j+1) is within bounds and within the band
            if (a[i] == b[j] && i + 1 <= N && j + 1 <= M) {
                if (abs((i + 1) - (j + 1)) < maxoffset_val) { // (i+1)-(j+1) == i-j, so this is always true if (i,j) is in band.
                    int v = 1 + dp[i + 1][(i + 1) - (j + 1) + maxoffset_val];
                    if (v > ret) ret = v, choice[i][current_offset] = 2;
                }
            }
            dp[i][current_offset] = ret;
        }
    }

    int lcs_len = dp[0][0 - 0 + maxoffset_val]; // LCS of a and b starting from (0,0)

    string ans = "";
    p2 state = p2(0, 0);

    // Reconstruct LCS string
    while (state.first < N && state.second < M &&
           abs(state.first - state.second) < maxoffset_val && // Ensure we are within the band we calculated
           choice[state.first][state.first - state.second + maxoffset_val] != -1) {
        int i, j;
        tie(i, j) = state;

        int current_offset = i - j + maxoffset_val;

        if (choice[i][current_offset] == 0) { // Came from (i+1, j)
            state.first++;
        } else if (choice[i][current_offset] == 1) { // Came from (i, j+1)
            state.second++;
        } else if (choice[i][current_offset] == 2) { // Came from (i+1, j+1) and matched
            ans += a[i];
            state.first++;
            state.second++;
        } else {
            // This case should ideally not be hit if choice is set correctly
            // or if we reach a base case. Break if no valid choice.
            break;
        }
    }

    cerr << lcs_len << "\n";
    cout << shortestCommonSupersequence(a, b, ans);

    return 0;
}
