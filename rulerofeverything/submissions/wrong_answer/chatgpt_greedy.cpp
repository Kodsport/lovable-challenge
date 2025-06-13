#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;
    cin >> N >> K;
    vector<ll>a(N), b(N);
    for(int i = 0; i < N; i++){
        cin >> a[i] >> b[i];
    }

    vector<bool> used(N,false);
    ll f = 0;
    int ans = 0;

    // Greedily pick the best video until we reach K or run out of improvements.
    while(f < K){
        ll bestVal = f;
        int bestIdx = -1;

        // Scan all unused videos in O(N)
        for(int i = 0; i < N; i++){
            if(used[i]) continue;
            ll val = a[i] * f + b[i];
            if(val > bestVal){
                bestVal = val;
                bestIdx = i;
            }
        }

        // If no video can increase f, we're stuck
        if(bestIdx == -1){
            cout << -1 << "\n";
            return 0;
        }

        // Use that video
        used[bestIdx] = true;
        f = bestVal;
        ans++;
    }

    cout << ans << "\n";
    return 0;
}
