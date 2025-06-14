// knows about optimal order argument. O(N^2)
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


// Simple Fraction class for exact arithmetic
class Fraction {
public:
    long long num;
    long long den;

    Fraction(long long n = 0, long long d = 1) {
        if (d < 0) n = -n, d = -d;
        long long g = std::gcd(n, d);
        num = n / g;
        den = d / g;
    }

    Fraction operator+(const Fraction& o) const { return Fraction(num * o.den + o.num * den, den * o.den); }
    Fraction operator-(const Fraction& o) const { return Fraction(num * o.den - o.num * den, den * o.den); }
    Fraction operator*(const Fraction& o) const { return Fraction(num * o.num, den * o.den); }
    Fraction operator/(const Fraction& o) const { return Fraction(num * o.den, den * o.num); }

    bool operator<(const Fraction& o) const { return num * o.den < o.num * den; }
    bool operator<=(const Fraction& o) const { return num * o.den <= o.num * den; }
    bool operator==(const Fraction& o) const { return num == o.num && den == o.den; }
    bool operator!=(const Fraction& o) const { return !(*this == o); }
    bool operator>(const Fraction& o) const { return o < *this; }
    bool operator>=(const Fraction& o) const { return o <= *this; }

    double to_double() const { return static_cast<double>(num) / den; }
};

// Piecewise-linear convex function using Fractions
class PLConvexFunc {
public:
    Fraction base_value;
    Fraction left_slope;
    std::vector<std::pair<Fraction, Fraction>> breakpoints;

    PLConvexFunc() : base_value(0), left_slope(1) {}
    PLConvexFunc(Fraction b, Fraction s) : base_value(b), left_slope(s) {}
    explicit PLConvexFunc(Fraction c) : base_value(c), left_slope(0) {}

    void affine_transform(const Fraction& a, const Fraction& b) {
        base_value = a * base_value + b;
        left_slope = a * left_slope;
        for (auto& bp : breakpoints)
            bp.second = bp.second * a;
    }

    Fraction evaluate_at(const Fraction& x) const {
        Fraction val = base_value + left_slope * x;
        for (auto& bp : breakpoints) {
            if (bp.first <= x)
                val = val + bp.second * (x - bp.first);
            else break;
        }
        return val;
    }

    Fraction slope_at(const Fraction& x) const {
        Fraction s = left_slope;
        for (auto& bp : breakpoints) {
            if (bp.first <= x)
                s = s + bp.second;
            else break;
        }
        return s;
    }

    PLConvexFunc max(const PLConvexFunc& g) const {
        PLConvexFunc h;
        // Case: both linear
        if (breakpoints.empty() && g.breakpoints.empty()) {
            Fraction f0 = base_value, g0 = g.base_value;
            Fraction fs = left_slope, gs = g.left_slope;
            if (f0 >= g0 && fs >= gs) return *this;
            if (g0 >= f0 && gs >= fs) return g;
            Fraction cx = (g0 - f0) / (fs - gs);
            Fraction delta = (fs > gs) ? (fs - gs) : (gs - fs);
            h.breakpoints.push_back({ cx, delta });
            h.left_slope = std::min(fs, gs);
            h.base_value = std::max(f0, g0);
            return h;
        }
        // Determine start
        Fraction x0 = Fraction(0);
        if (!breakpoints.empty() && breakpoints[0].first < x0) x0 = breakpoints[0].first;
        if (!g.breakpoints.empty() && g.breakpoints[0].first < x0) x0 = g.breakpoints[0].first;

        using Event = std::pair<Fraction, std::pair<int, Fraction>>;
        auto cmp = [](const Event& a, const Event& b) { return b.first < a.first; };
        std::priority_queue<Event, std::vector<Event>, decltype(cmp)> pq(cmp);

        for (auto& bp : breakpoints) pq.push({ bp.first, {0, bp.second} });
        for (auto& bp : g.breakpoints)    pq.push({ bp.first, {1, bp.second} });
        pq.push({ x0, {-1, 0} });

        Fraction cur_x = x0;
        Fraction f_val = evaluate_at(cur_x), g_val = g.evaluate_at(cur_x);
        Fraction f_sl = slope_at(cur_x), g_sl = g.slope_at(cur_x);
        Fraction h_sl = (f_val > g_val) ? f_sl : (g_val > f_val ? g_sl : std::max(f_sl, g_sl));
        Fraction h_val = (f_val > g_val) ? f_val : (g_val > f_val ? g_val : std::max(f_val, g_val));

        Fraction init_val = h_val, init_sl = h_sl;

        while (!pq.empty()) {
            auto [nx, data] = pq.top(); pq.pop();
            int type = data.first; Fraction delta = data.second;
            // merge duplicates
            while (!pq.empty() && pq.top().first == nx) {
                auto d = pq.top().second; pq.pop();
                if (d.first == 0) f_sl = f_sl + d.second;
                else if (d.first == 1) g_sl = g_sl + d.second;
            }
            Fraction step = nx - cur_x;
            Fraction nf = f_val + f_sl * step;
            Fraction ng = g_val + g_sl * step;
            // crossing
            if (f_sl != g_sl) {
                Fraction cx = (g_val - f_val) / (f_sl - g_sl) + cur_x;
                if (cx > cur_x && cx < nx) {
                    pq.push({ nx, {type, delta} });
                    nx = cx;
                    step = nx - cur_x;
                    nf = f_val + f_sl * step;
                    ng = g_val + g_sl * step;
                    type = -2;
                }
            }
            cur_x = nx; f_val = nf; g_val = ng;
            h_val = (f_val > g_val) ? f_val : (g_val > f_val ? g_val : std::max(f_val, g_val));

            if (type == 0) f_sl = f_sl + delta;
            else if (type == 1) g_sl = g_sl + delta;
            else if (type == -1) h.base_value = h_val;

            Fraction new_sl = (f_val > g_val) ? f_sl : (g_val > f_val ? g_sl : std::max(f_sl, g_sl));
            if (new_sl != h_sl) {
                Fraction sd = new_sl - h_sl;
                if (sd > Fraction(0)) h.breakpoints.push_back({ cur_x, sd });
                h_sl = new_sl;
            }
        }

        // finalize
        if (h.breakpoints.empty()) {
            h.left_slope = init_sl;
            h.base_value = init_val - init_sl * x0;
        }
        else {
            h.left_slope = init_sl;
            if (h.base_value.num == 0 && h.base_value.den == 1) {
                Fraction integ = init_sl * (Fraction(0) - x0);
                for (auto& bp : h.breakpoints)
                    if (bp.first < Fraction(0)) integ = integ + bp.second * (Fraction(0) - bp.first);
                h.base_value = init_val + integ;
            }
        }
        std::sort(h.breakpoints.begin(), h.breakpoints.end(), [](auto& a, auto& b) {return a.first < b.first; });
        return h;
    }
};

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;


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

    vector<PLConvexFunc> fn(38);
    rep(i, sz(vids))
    {
        for (int j = 36; j > 0; j--)
        {
            assert(j != 0);
            PLConvexFunc c = fn[j - 1];
            c.affine_transform(vids[i].first, vids[i].second);
            fn[j] = fn[j].max(c);
        }
    }

    while (q--)
    {
        int k;
        cin >> k;


        int ans = inf;
        int p = 0;

        auto min_nonone = [&](int p)
            {
                rep(j, sz(fn))
                {
                    if (fn[j].evaluate_at(p) >= k)
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
        cout << ans << " ";
    }

    //rep(i, 36)
    //{
    //    cout << fn[i].breakpoints.size() << "\n";
    //}

    return 0;
}
