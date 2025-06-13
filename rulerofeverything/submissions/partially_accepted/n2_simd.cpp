#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <immintrin.h>
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = (ll)1e18;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll t;
    cin >> n >> t;

    vector<pair<ll,ll>> vids(n);
    for(auto &v: vids) 
        cin >> v.first >> v.second;

    // sort by your optimal-order comparator
    sort(vids.begin(), vids.end(), [&](auto &A, auto &B){
        // same as: A.second*B.first + B.second   >   B.second*A.first + A.second
        return A.second * B.first + B.second 
             > B.second * A.first + A.second;
    });

    // dp[j] = max achievable value of "time" using exactly j videos
    // initialize to -1 (impossible), except dp[0] = 0
    vector<ll> dp(n+1, -1);
    dp[0] = 0;

    for(int i = 0; i < n; i++){
        ll a = vids[i].first, b = vids[i].second;

        // iterate j DOWNWARDS so dp[j] on RHS is from previous iteration
        
        // assume dp is 64‑bit signed (ll), length >= i+2
        // a,b are ll
        int len = i + 1;           // number of valid dp[j]
        // process in blocks of 4, j descending
        int vec_blocks = len / 4;
        int rem        = len % 4;

        __m256i va = _mm256_set1_epi64x(a);
        __m256i vb = _mm256_set1_epi64x(b);

        for(int bi = 0; bi < vec_blocks; bi++){
            // compute starting j for this block (descending)
            int j = len - (bi+1)*4;
            // load dp[j..j+3]
            __m256i vdp_j = _mm256_loadu_si256((__m256i const*)&dp[j]);
            // multiply: each 64‑bit lane
            // Note: AVX2 has only _mm256_mul_epi32 which multiplies 32‑bit → 64‑bit on pairs.
            //       here we assume values fit in 32 bits or use two 128‑bit lanes:
            __m256i prod_lo = _mm256_mul_epi32(vdp_j, va);
            __m256i prod_hi = _mm256_mul_epi32(_mm256_srli_epi64(vdp_j,32),
                                            _mm256_srli_epi64(va,32));
            // reconstruct full 64×4: interleave low/high parts
            __m256i prod = _mm256_blend_epi32(prod_lo,
                            _mm256_slli_epi64(prod_hi, 32), 0b1010);

            // add b
            __m256i cand = _mm256_add_epi64(prod, vb);

            // load dp[j+1..j+4]
            __m256i vdp_next = _mm256_loadu_si256((__m256i const*)&dp[j+1]);
            // max
           __m256i mask = _mm256_cmpgt_epi64(cand, vdp_next);
            __m256i vmax = _mm256_blendv_epi8(vdp_next, cand, mask);

            // store back
            _mm256_storeu_si256((__m256i*)&dp[j+1], vmax);
        }

        // handle the leftover scalar tail
        for(int j = rem - 1; j >= 0; j--){
            int idx = j;
            dp[idx+1] = max(dp[idx+1], dp[idx]*a + b);
        }
        for (int j=0; j<n;j++) dp[j] = min(dp[j], t);
    }

    // find the smallest j such that dp[j] >= t
    int ans = -1;
    for(int j = 0; j <= n; j++){
        if(dp[j] >= t){
            ans = j;
            break;
        }
    }

    cout << ans << "\n";
    return 0;
}
