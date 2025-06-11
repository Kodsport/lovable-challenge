#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;  if(!(cin >> N)) return 0;
    vector<int64> a(N);
    for (auto &x : a) cin >> x;
    sort(a.begin(), a.end());

    // case |S0| odd
    if (N & 1) { cout << 1 << '\n'; return 0; }

    long long ans = 0;               // seconds spent so far

    while (true)
    {
        // compute gap-parity  P(a)  and   check “all even”
        int parity = 0;              // xor of (a[2i]-a[2i-1])&1
        bool allEven = true;

        for (int i = 0; i < N; i += 2) {
            parity ^= ( (a[i+1] - a[i]) & 1 );
            if ( (a[i] & 1) || (a[i+1] & 1) )      // only N even ⇒ i+1 valid
                allEven = false;
        }

        if (parity) {                        // |f(S)| is odd
            cout << ans + 2 << '\n';         //  -> infinite two sec later
            break;
        }

        if (!allEven) {                      // mixed parity, done in 2 more sec
            cout << ans + 2 << '\n';
            break;
        }

        /* every number is even:   halve & continue */
        for (auto &x : a) x >>= 1;
        ans = ans * 2 + 1;                   // doubling rule
    }
    return 0;
}
