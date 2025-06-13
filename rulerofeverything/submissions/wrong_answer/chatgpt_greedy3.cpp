#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll K;
    cin >> N >> K;

    vector<ll> adds;
    struct M { int a; int b; long double key; };
    vector<M> muls;

    for(int i = 0; i < N; i++){
        int a, b;
        cin >> a >> b;
        if(a == 1){
            adds.push_back(b);
        } else {
            // key = b/(a-1)
            muls.push_back({a, b, (long double)b / (a - 1)});
        }
    }

    // sort the pure adds descending by b
    sort(adds.begin(), adds.end(), greater<ll>());

    // sort the multiplies descending by key = b/(a-1)
    sort(muls.begin(), muls.end(), [](auto &x, auto &y){
        return x.key > y.key;
    });

    ll f = 0;
    int used = 0;

    // first use as many adds as needed
    for(ll b : adds){
        f += b;
        used++;
        if(f >= K){
            cout << used << "\n";
            return 0;
        }
    }

    // then the multiplies
    for(auto &op : muls){
        f = op.a * f + op.b;
        used++;
        if(f >= K){
            cout << used << "\n";
            return 0;
        }
    }

    // even after all N ops we didn't reach K
    cout << used << "\n";
    return 0;
}
