#include <bits/stdc++.h>
using namespace std;

#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

using pii = pair<int,int>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// Greedy single‐pass (A→B)
vector<pii> greedy_pairs(const string &A, const string &B){
    int n = A.size(), m = B.size();
    vector<vector<int>> pos(256);
    for(int j = 0; j < m; ++j)
        pos[(unsigned char)B[j]].push_back(j);
    vector<pii> res;
    res.reserve(min(n,m));
    int last = -1;
    for(int i = 0; i < n; ++i){
        auto &v = pos[(unsigned char)A[i]];
        auto it = upper_bound(v.begin(), v.end(), last);
        if(it != v.end()){
            last = *it;
            res.emplace_back(i, last);
        }
    }
    return res;
}

// Four‑way greedy seed
vector<pii> seed_greedy(const string &A, const string &B){
    // 1) A→B
    auto best = greedy_pairs(A,B);

    // 2) B→A
    {
        auto t = greedy_pairs(B,A);
        for(auto &p : t) swap(p.first,p.second);
        reverse(t.begin(), t.end());
        if(t.size() > best.size()) best = t;
    }

    // 3) rev(A)→rev(B)
    {
        string Ar = A, Br = B;
        reverse(Ar.begin(), Ar.end());
        reverse(Br.begin(), Br.end());
        auto t = greedy_pairs(Ar, Br);
        vector<pii> tmp;
        tmp.reserve(t.size());
        int nA = A.size(), nB = B.size();
        for(auto &p : t){
            // map back into original indices
            int ai = (nA - 1) - p.first;
            int bi = (nB - 1) - p.second;
            tmp.emplace_back(ai, bi);
        }
        reverse(tmp.begin(), tmp.end());
        if(tmp.size() > best.size()) best = move(tmp);
    }

    // 4) rev(B)→rev(A)
    {
        string Ar = A, Br = B;
        reverse(Ar.begin(), Ar.end());
        reverse(Br.begin(), Br.end());
        auto t = greedy_pairs(Br, Ar);
        vector<pii> tmp;
        tmp.reserve(t.size());
        int nA = A.size(), nB = B.size();
        for(auto &p : t){
            int ai = (nA - 1) - p.second;
            int bi = (nB - 1) - p.first;
            tmp.emplace_back(ai, bi);
        }
        reverse(tmp.begin(), tmp.end());
        if(tmp.size() > best.size()) best = move(tmp);
    }

    return best;
}

// Check validity of matched-pairs subsequence
bool valid_pairs(const vector<pii>& v){
    for(int k = 1; k < (int)v.size(); ++k){
        if(v[k-1].first  >= v[k].first ||
           v[k-1].second >= v[k].second)
            return false;
    }
    return true;
}

// Energy = -length
inline double energy(const vector<pii> &v){
    return -double(v.size());
}

// Simulated annealing over match‑pairs
vector<pii> simulated_anneal(
    const string &A, const string &B,
    vector<pii> init,
    double T0,
    double Tend,
    int max_iters
){
    auto best = init;
    auto curr = init;
    double Ebest = energy(best);
    double Ec    = energy(curr);

    int n = A.size(), m = B.size();
    // precompute pos lists for B
    vector<vector<int>> posB(256);
    for(int j = 0; j < m; ++j)
        posB[(unsigned char)B[j]].push_back(j);


    auto start = chrono::high_resolution_clock::now();
    while (1) {
        double t = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now()-start).count() / 1000.;
        if (t>0.95) break;
        double T = T0 * pow(Tend/T0, t);

        vector<pii> cand = curr;

        // pick a move type
        int mv = rng() % 3;
        if(mv == 0 && !cand.empty()){
            // re‑match one
            int k = rng() % cand.size();
            int i = cand[k].first;
            int lo = (k > 0 ? cand[k-1].second + 1 : 0);
            int hi = (k+1 < (int)cand.size() ? cand[k+1].second - 1 : m-1);
            auto &v = posB[(unsigned char)A[i]];
            auto it_lo = lower_bound(v.begin(), v.end(), lo);
            auto it_hi = upper_bound(v.begin(), v.end(), hi);
            if(it_lo < it_hi){
                int idx = uniform_int_distribution<int>(0, it_hi - it_lo - 1)(rng);
                cand[k].second = it_lo[idx];
            }
        }
        else if(mv == 1 && !cand.empty()){
            // delete one
            int k = rng() % cand.size();
            cand.erase(cand.begin() + k);
        }
        else {
            // insert one
            int i = rng() % n;
            auto &v = posB[(unsigned char)A[i]];
            if(!v.empty()){
                int j = v[rng() % v.size()];
                auto it = lower_bound(cand.begin(), cand.end(), pii(i,j));
                cand.insert(it, {i,j});
            }
        }

        // validate
        if(!valid_pairs(cand)) continue;
        double Ecand = energy(cand);
        double dE = Ecand - Ec;
        if(dE < 0 || exp(-dE/T) > uniform_real_distribution<double>(0,1.0)(rng)){
            curr = move(cand);
            Ec   = Ecand;
            if(Ec < Ebest){
                best = curr;
                Ebest = Ec;
            }
        }
    }

    return best;
}

string lcs(const string& a, const string& b) {
    auto seed = seed_greedy(a, b);
    auto sol = simulated_anneal(a, b, seed, 100.0, 1e-3, 50000);
    string res;
    res.reserve(sol.size());
    for (auto& p : sol) res += a[p.first];
    return res;
}


string shortestCommonSupersequence(string& A, string& B, const string& lcs) {
    cerr << "lcs length:" << lcs.size() << "\n";
    string scs;
    scs.reserve(A.size() + B.size());
    int i = 0, j = 0;
    for (char c : lcs) {
        while (i < (int)A.size() && A[i] != c) scs.push_back(A[i++]);
        while (j < (int)B.size() && B[j] != c) scs.push_back(B[j++]);
        scs.push_back(c);
        ++i; ++j;
    }
    if (i < (int)A.size()) scs.append(A, i, string::npos);
    if (j < (int)B.size()) scs.append(B, j, string::npos);
    return scs;
}


signed main()
{
    string a, b;
    cin >> a >> b;

    cout << shortestCommonSupersequence(
        a, b,
        lcs(a,b)
    );

}