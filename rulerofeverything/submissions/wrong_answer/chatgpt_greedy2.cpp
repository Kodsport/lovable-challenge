#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N; ll K;
    cin >> N >> K;
    struct Op { 
        int a; 
        int b; 
        double key;
    };
    vector<Op> ops(N);

    for(int i = 0; i < N; i++){
        cin >> ops[i].a >> ops[i].b;
        if(ops[i].a == 1){
            ops[i].key = 1e300;  // "infinity"
        } else {
            ops[i].key = double(ops[i].b) / double(ops[i].a - 1);
        }
    }

    // sort descending by key
    sort(ops.begin(), ops.end(), [](auto &x, auto &y){
        return x.key > y.key;
    });

    ll f = 0;
    int used = 0;
    for(auto &op : ops){
        f = op.a * f + op.b;
        used++;
        if(f >= K){
            cout << used << "\n";
            return 0;
        }
    }

    // even after all, never reached K
    cout << used << "\n";
    return 0;
}
