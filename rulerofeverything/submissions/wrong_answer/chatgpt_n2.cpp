#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;
    cin >> N >> K;

    vector<ll> a(N), b(N);
    for(int i = 0; i < N; i++){
        cin >> a[i] >> b[i];
    }

    // dp[k] = maximum followers reachable using exactly k videos
    const ll NEG_INF = -1;           
    vector<ll> dp(N+1, NEG_INF);
    dp[0] = 0;  // 0 videos → 0 followers

    // For each video i, try appending it to all sequences of length k
    for(int i = 0; i < N; i++){
        // go backwards so we don't reuse video i multiple times
        for(int k = i; k >= 0; k--){
            if(dp[k] >= 0){
                ll cand = a[i] * dp[k] + b[i];
                dp[k+1] = max(dp[k+1], cand);
            }
        }
    }

    // Find the minimal k with dp[k] ≥ K
    for(int k = 0; k <= N; k++){
        if(dp[k] >= K){
            cout << k << "\n";
            return 0;
        }
    }

    // If no k works, it’s impossible
    cout << -1 << "\n";
    return 0;
}
