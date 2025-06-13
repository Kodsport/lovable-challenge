#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll NEG_INF = LLONG_MIN;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll t;
    cin >> n >> t;
    vector<pair<ll, ll>> vids(n);
    for (int i = 0; i < n; i++) {
        cin >> vids[i].first >> vids[i].second;
    }

    // Group by multiplier 'a'
    sort(vids.begin(), vids.end());
    vector<ll> A;              // unique a's
    vector<vector<ll>> B;      // B[i] list of b's for group i
    for (int i = 0; i < n; ) {
        int j = i;
        A.push_back(vids[i].first);
        B.emplace_back();
        while (j < n && vids[j].first == vids[i].first) {
            B.back().push_back(vids[j].second);
            j++;
        }
        // sort desc for larger gains first
        sort(B.back().rbegin(), B.back().rend());
        i = j;
    }
    int G = A.size();

    // Precompute state-space size and multipliers for bijection
    vector<int> base(G);
    long long states = 1;
    for (int i = 0; i < G; i++) {
        base[i] = B[i].size() + 1;
        states *= base[i];
    }
    vector<ll> multiplier(G, 1);
    for (int i = 1; i < G; i++) {
        multiplier[i] = multiplier[i - 1] * base[i - 1];
    }

    // For each state-id, store best "subs" achieved
    vector<ll> bestSubs(states, NEG_INF);

    // BFS over number of picks (taken)
    deque<long long> q;
    // state encoded counts all zero => id 0
    bestSubs[0] = 0;
    q.push_back(0);
    int taken = 0;

    // sentinel for level separation
    q.push_back(-1);
    while (!q.empty()) {
        ll sid = q.front(); q.pop_front();
        if (sid == -1) {
            taken++;
            if (q.empty()) break;
            q.push_back(-1);
            continue;
        }
        ll currentSubs = bestSubs[sid];
        // try any group pick
        for (int i = 0; i < G; i++) {
            // decode count at group i
            int cnt = (sid / multiplier[i]) % base[i];
            if (cnt + 1 >= base[i]) continue;  // already exhausted
            // new state id
            ll nid = sid + multiplier[i];
            // compute new subs
            ll b = B[i][cnt];
            ll nsubs = currentSubs * A[i] + b;
            if (nsubs > bestSubs[nid]) {
                if (nsubs >= t) {
                    cout << taken+1 << "\n";
                    return 0;
                }
                bestSubs[nid] = nsubs;
                q.push_back(nid);
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
