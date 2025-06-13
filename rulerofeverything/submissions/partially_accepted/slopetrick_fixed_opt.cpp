// knows about optimal order argument. O(???)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int ceildiv(int a, int b)
{
    a = abs(a); b = abs(b);
    return (a + b - 1) / b;
}

class PLConvexFunc {
public:
    double base_value;  // Value at x=0
    double left_slope;  // Slope for x < first breakpoint
    struct line
    {
        int base_value, slope;
        int isect(const line& other) const {
            int delta_slope = slope - other.slope;
            int delta_base = other.base_value - base_value;

            assert(delta_slope != 0); // lines must not be parallel

            return ceildiv(delta_base, delta_slope);
        }
        double floatisect(const line& other) const {
            int delta_slope = slope - other.slope;
            int delta_base = other.base_value - base_value;

            assert(delta_slope != 0); // lines must not be parallel

            return double(delta_base) / delta_slope;
        }
        int eval(int x)
        {
            return slope * x + base_value;
        }
    };
    std::vector<std::pair<double, double>> breakpoints;  // Sorted (x, delta) pairs, delta > 0

    // Constructors
    PLConvexFunc() : base_value(0), left_slope(1) {}
    PLConvexFunc(double base, double slope) : base_value(base), left_slope(slope) {}
    explicit PLConvexFunc(double constant) : base_value(constant), left_slope(0) {}

    // Apply affine transformation: f(x) becomes a*f(x) + b (a > 0)
    void affine_transform(double a, double b) {
        base_value = a * base_value + b;
        left_slope = a * left_slope;
        for (auto& bp : breakpoints) {
            bp.second *= a;
        }
    }

    // Evaluate function at point x
    double evaluate_at(double x) const {
        double value = base_value + left_slope * x;
        for (const auto& bp : breakpoints) {
            if (bp.first <= x) {
                value += bp.second * (x - bp.first);
            }
            else {
                break;  // Breakpoints are sorted
            }
        }
        return value;
    }

    // Compute current slope at point x (right-derivative)
    double slope_at(double x) const {
        double slope = left_slope;
        for (const auto& bp : breakpoints) {
            if (bp.first <= x) {
                slope += bp.second;
            }
            else {
                break;
            }
        }
        return slope;
    }

    // Iterate-through approach for max of two PLConvexFunc
    void max(const PLConvexFunc& g) {
        PLConvexFunc& f = *this;
        PLConvexFunc h;

        // handle both-linear special case
        if (f.breakpoints.empty() && g.breakpoints.empty()) {
            // ... existing linear case unchanged ...
            int f0 = f.base_value;
            int g0 = g.base_value;
            int fs = f.left_slope;
            int gs = g.left_slope;
            if (f0 >= g0 && fs >= gs) return;
            if (g0 >= f0 && gs >= fs) {
                f.base_value = g0;
                f.left_slope = gs;
                return;
            }
            double xc = line{ f0,fs }.floatisect({ g0,gs });
            f.base_value = std::max(f0, g0);
            f.left_slope = std::min(fs, gs);
            f.breakpoints = { {xc, std::abs(fs - gs)} };
            return;
        }

        // General case: scan through sorted breakpoints of f and g
        auto& A = f.breakpoints;
        auto& B = g.breakpoints;
        size_t i = 0, j = 0;
        double cur_x = 0.0;
        int fs = f.left_slope;
        int gs = g.left_slope;
        double fv = f.base_value;
        double gv = g.base_value;

        // initialize h at x=0
        double d = fv - gv;
        int hs = (d > 0 ? fs : (d < 0 ? gs : std::max(fs, gs)));
        h.base_value = std::max((int)fv, (int)gv);
        h.left_slope = hs;

        while (i < A.size() || j < B.size()) {
            double nextA = (i < A.size() ? A[i].first : std::numeric_limits<double>::infinity());
            double nextB = (j < B.size() ? B[j].first : std::numeric_limits<double>::infinity());
            double next_x;
            enum Src { ONLY_F, ONLY_G, BOTH } source;

            if (nextA < nextB) {
                next_x = nextA;
                source = ONLY_F;
            }
            else if (nextB < nextA) {
                next_x = nextB;
                source = ONLY_G;
            }
            else {  // simultaneous
                next_x = nextA;
                source = BOTH;
            }

            // detect crossing in (cur_x, next_x)
            double dx = next_x - cur_x;
            int ds = fs - gs;
            double d_end = d + ds * dx;
            if (ds != 0 && d * d_end < 0) {
                double xc = cur_x - d / ds;
                int old_s = (d > 0 ? fs : gs);
                int new_s = (d > 0 ? gs : fs);
                h.breakpoints.emplace_back(xc, std::abs(new_s - old_s));
                // advance to xc
                fv += fs * (xc - cur_x);
                gv += gs * (xc - cur_x);
                cur_x = xc;
                d = 0;
                hs = new_s;
            }

            // advance to next_x
            fv += fs * (next_x - cur_x);
            gv += gs * (next_x - cur_x);
            cur_x = next_x;
            d = fv - gv;

            // update slopes based on source
            if (source == ONLY_F) {
                fs += A[i].second;
                i++;
            }
            else if (source == ONLY_G) {
                gs += B[j].second;
                j++;
            }
            else {  // BOTH
                fs += A[i].second;
                gs += B[j].second;
                i++; j++;
            }

            // check if max slope changed
            int new_hs = (d > 0 ? fs : (d < 0 ? gs : std::max(fs, gs)));
            if (new_hs != hs) {
                h.breakpoints.emplace_back(cur_x, std::abs(new_hs - hs));
                hs = new_hs;
            }
        }

        // final crossing beyond last breakpoint
        {
            int ds = fs - gs;
            if (ds != 0 && d * ds < 0) {
                double xc = cur_x - d / ds;
                int old_s = (d > 0 ? fs : gs);
                int new_s = (d > 0 ? gs : fs);
                h.breakpoints.emplace_back(xc, std::abs(new_s - old_s));
            }
        }

        // adopt h
        *this = std::move(h);
    }


};

signed main()
{
    fast();

#if _LOCAL
    ifstream in("e:/in.txt");
    cin.rdbuf(in.rdbuf());
#endif

    int n, t;
    cin >> n >> t;

    vi ones;

    vector<p2> vids;
    rep(i, n)
    {
        int a, b;
        cin >> a >> b;
        if (a == 1) ones.push_back(b);
        else vids.emplace_back(a, b);
    }
    sort(all(ones));
    reverse(all(ones));
    sort(all(vids), [](p2 a, p2 b)
        {
            return (a.second) * (b.first - 1) > b.second * (a.first - 1);
        });

    double tot_cost = 0;
    double max_vids = 0;
    vector<PLConvexFunc> fn(36);
    vi done(36);
    rep(i, sz(vids))
    {
        for (int j = 34; j > 0; j--)
        {
            //assert(!(j == 1 && i==2));
            //assert(!(j == 1 && i==1));
            if (done[j]) continue;
            PLConvexFunc c = fn[j - 1];
            c.affine_transform(vids[i].first, vids[i].second);
            fn[j].max(c);
            tot_cost += fn[j].breakpoints.size();
            max_vids = max(max_vids, (double)fn[j].breakpoints.size());
            if (fn[j].base_value >= t)
            {
                repp(k, j, 36) done[k] = 1;
            }
        }
    }


    int ans = inf;
    int p = 0;

    auto min_nonone = [&](int p)
        {
            rep(j, sz(fn))
            {
                if (fn[j].evaluate_at(p) >= t)
                {
                    return j;
                }
            }
            return inf;
        };

    rep(i, sz(ones))
    {
        ans = min(ans, i + min_nonone(p));
        p += ones[i];
    }
    ans = min(ans, sz(ones) + min_nonone(p));
    if (ans == inf) ans = -1;
    cout << ans << "\n";

    cerr << (sz(vids) ? tot_cost / sz(vids) : 0) << " " << max_vids;
    // int tot_bp = 0;
    // rep(i, 36) tot_bp += sz(fn[i].breakpoints);
    // cout << tot_bp;

    return 0;
}
