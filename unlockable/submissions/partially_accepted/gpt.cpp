#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    long long N, a;
    cin >> N >> a;

    unordered_set<long long> b;
    b.reserve(N);
    long long x;
    long long largest = 0;
    for (int i = 0; i < N; i++) {
        cin >> x;
        b.insert(x);
        if (x > largest) largest = x;
    }

    long long out = 0;

    // Compute powers of a iteratively
    // Start with a^1 = a
    for (int exp = 1; exp < 64; exp++) {
        // Compute a^exp
        static long long p = 0;
        if (exp == 1) {
            p = a;
        } else {
            // multiply previous power by a, 
            // but guard against overflow
            if (p > largest / a) break;
            p *= a;
        }
        if (p > largest) break;

        // Now for each y >= 1 such that y*p <= largest
        long long maxY = largest / p;
        for (long long y = 1; y <= maxY; y++) {
            if (b.count(y * p)) {
                out++;
            }
        }
    }

    cout << out << "\n";
    return 0;
}
