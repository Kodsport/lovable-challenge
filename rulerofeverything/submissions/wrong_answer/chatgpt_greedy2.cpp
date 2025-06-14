#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, q;
    cin >> N >> q;
    struct Op {
        int a;
        int b;
        double key;
    };
    vector<Op> ops(N);

    for (int i = 0; i < N; i++) {
        cin >> ops[i].a >> ops[i].b;
        if (ops[i].a == 1) {
            ops[i].key = 1e300;  // "infinity"
        }
        else {
            ops[i].key = double(ops[i].b) / double(ops[i].a - 1);
        }
    }

    // sort descending by key
    sort(ops.begin(), ops.end(), [](auto& x, auto& y) {
        return x.key > y.key;
        });

    while (q--)
    {
        ll K;
        cin >> K;

        ll f = 0;
        int used = 0;
        for (auto& op : ops) {
            f = op.a * f + op.b;
            used++;
            if (f >= K) {
                cout << used << " ";
                goto done;
            }
        }

        // even after all, never reached K
        cout << "-1 ";
        done:;
    }

    return 0;
}
