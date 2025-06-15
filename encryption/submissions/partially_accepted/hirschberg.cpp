#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::max

using namespace std;

// Function to compute the scores for the last row of the DP table
// in O(min(m, n)) space. This is a core component of Hirschberg's algorithm.
// It returns a vector representing the scores (lengths of LCS) for each
// prefix of the second string, when comparing against the full first string.
std::vector<int> compute_lcs_scores(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();

    // dp[j] will store the length of LCS of s1[0...i] and s2[0...j]
    // using only two rows of space.
    std::vector<int> prev_row(n + 1, 0);
    std::vector<int> curr_row(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1]) {
                curr_row[j] = prev_row[j - 1] + 1;
            } else {
                curr_row[j] = std::max(curr_row[j - 1], prev_row[j]);
            }
        }
        prev_row = curr_row; // Move current_row to prev_row for the next iteration
    }
    return curr_row; // The last computed row contains the scores
}

// Hirschberg's Algorithm for LCS
std::string hirschberg_lcs(const std::string& s1, const std::string& s2) {
    int m = s1.length();
    int n = s2.length();

    // Base cases
    if (m == 0 || n == 0) {
        return "";
    }
    if (m == 1) { // If one string has length 1
        for (char c : s2) {
            if (s1[0] == c) {
                return std::string(1, s1[0]);
            }
        }
        return "";
    }
    if (n == 1) { // If other string has length 1
        for (char c : s1) {
            if (s2[0] == c) {
                return std::string(1, s2[0]);
            }
        }
        return "";
    }

    // Divide step
    int mid_s1 = m / 2;

    // Split s1 into s1_left and s1_right (reversed)
    std::string s1_left = s1.substr(0, mid_s1);
    std::string s1_right_rev = s1.substr(mid_s1);
    std::reverse(s1_right_rev.begin(), s1_right_rev.end());

    // Compute scores for the first half using s1_left and s2
    std::vector<int> score_left = compute_lcs_scores(s1_left, s2);

    // Compute scores for the second half using reversed strings
    // s1_right_rev and s2_rev. This allows us to find the split point in s2.
    std::string s2_rev = s2;
    std::reverse(s2_rev.begin(), s2_rev.end());
    std::vector<int> score_right = compute_lcs_scores(s1_right_rev, s2_rev);
    std::reverse(score_right.begin(), score_right.end()); // Reverse scores back

    // Find the split point (k) in s2 that maximizes the sum of scores
    int max_score_sum = -1;
    int k = 0; // Split point in s2
    for (int j = 0; j <= n; ++j) {
        int current_sum = score_left[j] + score_right[j];
        if (current_sum > max_score_sum) {
            max_score_sum = current_sum;
            k = j;
        }
    }

    // Conquer step: Recursively solve for the two subproblems
    std::string lcs_left = hirschberg_lcs(s1.substr(0, mid_s1), s2.substr(0, k));
    std::string lcs_right = hirschberg_lcs(s1.substr(mid_s1), s2.substr(k));

    return lcs_left + lcs_right;
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


int main() {
    string a, b;
    cin >> a >> b;

    cout << shortestCommonSupersequence(a, b, hirschberg_lcs(a, b));

    
    return 0;
}