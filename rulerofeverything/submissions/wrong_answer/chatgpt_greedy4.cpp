#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

const ll maxK = ll(8e9) + 10;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, q;
    cin >> N >> q;

    vector<ll> adds;
    struct Mul { int a; int b; long double key; };
    vector<Mul> muls;

    for (int i = 0; i < N; i++) {
        int a, b;
        cin >> a >> b;
        if (a == 1) {
            adds.push_back(b);
        }
        else {
            muls.push_back({ a, b, (long double)b / (a - 1) });
        }
    }

    // 1) sort and prefix-sum for adds
    sort(adds.begin(), adds.end(), greater<ll>());
    int A = adds.size();
    vector<ll> S(A + 1, 0);
    for (int i = 1; i <= A; i++) {
        S[i] = min(S[i - 1] + adds[i - 1], maxK);
    }

    // 2) sort and build P[], C[] for multiplies
    sort(muls.begin(), muls.end(),
        [&](auto& L, auto& R) { return L.key > R.key; });
    int M = muls.size();
    vector<ll> P(M + 1, 1), C(M + 1, 0);
    for (int i = 1; i <= M; i++) {
        // clamp product so it never exceeds K
        __int128 p = (__int128)P[i - 1] * muls[i - 1].a;
        P[i] = (p >= maxK ? maxK : (ll)p);

        // new constant term = a * oldC + b
        __int128 c = (__int128)muls[i - 1].a * C[i - 1] + muls[i - 1].b;
        C[i] = (c >= maxK ? maxK : (ll)c);
    }

    // check(m): can we reach >=K with exactly m videos?
    auto can = [&](int m, ll K) {
        // try all y = number of multiplies used
        for (int y = 0; y <= M && y <= m; y++) {
            int x = m - y;
            if (x > A) continue;
            // f = P[y] * S[x] + C[y], in 128-bit
            __int128 f = (__int128)P[y] * S[x] + C[y];
            if (f >= K) return true;
        }
        return false;
        };

    while (q--)
    {
        ll K;
        cin >> K;
        // 3) binary search smallest m in [1..N] with can(m)=true
        int lo = 1, hi = N, ans = N + 1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (can(mid, K)) {
                ans = mid;
                hi = mid - 1;
            }
            else {
                lo = mid + 1;
            }
        }

        // if ans stayed N+1, you can't ever reach K; otherwise ans is our answer
        cout << (ans <= N ? ans : N) << " ";
    }

    
    return 0;
}
