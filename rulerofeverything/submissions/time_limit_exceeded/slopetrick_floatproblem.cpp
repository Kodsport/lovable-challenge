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

// chatgpt-generated code.
// fast representation of piecewise linear convex functions
// can apply affine transformations, evaluate point and take max with another function
class PLConvexFunc {
public:
    double base_value;  // Value at x=0
    double left_slope;  // Slope for x < first breakpoint
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

    // Compute pointwise maximum with another convex function
    PLConvexFunc max(const PLConvexFunc& g) const {
        PLConvexFunc h;
        if (breakpoints.empty() && g.breakpoints.empty()) {
            // Both functions are linear
            double f0 = base_value;
            double g0 = g.base_value;
            double f_slope = left_slope;
            double g_slope = g.left_slope;

            if (f0 >= g0 && f_slope >= g_slope) return *this;
            if (g0 >= f0 && g_slope >= f_slope) return g;

            double cross_x = (g0 - f0) / (f_slope - g_slope);
            h.breakpoints.push_back({ cross_x, std::abs(f_slope - g_slope) });
            h.left_slope = std::min(f_slope, g_slope);
            h.base_value = std::max(f0, g0);
            return h;
        }

        // Find starting point (min of smallest breakpoint and 0)
        double x0 = 0.0;
        if (!breakpoints.empty()) x0 = std::min(x0, breakpoints[0].first);
        if (!g.breakpoints.empty()) x0 = std::min(x0, g.breakpoints[0].first);

        // Create event queue: (x, type, delta)
        using Event = std::pair<double, std::pair<int, double>>;
        auto cmp = [](const Event& a, const Event& b) { return a.first > b.first; };
        std::priority_queue<Event, std::vector<Event>, decltype(cmp)> events(cmp);

        for (const auto& bp : breakpoints)
            events.push({ bp.first, {0, bp.second} });
        for (const auto& bp : g.breakpoints)
            events.push({ bp.first, {1, bp.second} });
        if (0.0 >= x0)
            events.push({ 0.0, {-1, 0.0} });  // Special event to record value at 0

        // Initialize values and slopes
        double cur_x = x0;
        double f_val = evaluate_at(x0);
        double g_val = g.evaluate_at(x0);
        double f_slope = slope_at(x0);
        double g_slope = g.slope_at(x0);
        double h_val = std::max(f_val, g_val);
        double h_slope = (f_val > g_val) ? f_slope :
            (g_val > f_val) ? g_slope :
            std::max(f_slope, g_slope);

        // Store initial values for integration later
        const double init_h_val = h_val;
        const double init_h_slope = h_slope;

        // Process events
        while (!events.empty()) {
            double next_x = events.top().first;
            int type = events.top().second.first;
            double delta = events.top().second.second;
            events.pop();

            // Skip duplicate events at same x
            while (!events.empty() && events.top().first == next_x) {
                auto [x, data] = events.top();
                auto [t, d] = data;
                events.pop();
                if (t == 0) f_slope += d;
                else if (t == 1) g_slope += d;
            }

            // Calculate values at next_x
            double step = next_x - cur_x;
            double next_f_val = f_val + f_slope * step;
            double next_g_val = g_val + g_slope * step;

            // Check for crossing point
            double cross_x = std::numeric_limits<double>::lowest();
            if (f_slope != g_slope) {
                cross_x = cur_x + (g_val - f_val) / (f_slope - g_slope);
                if (cross_x > cur_x && cross_x < next_x) {
                    events.push({ next_x, {type, delta} });
                    next_x = cross_x;
                    step = next_x - cur_x;
                    next_f_val = f_val + f_slope * step;
                    next_g_val = g_val + g_slope * step;
                    type = -2;  // Crossing event
                }
            }

            // Update current state
            cur_x = next_x;
            f_val = next_f_val;
            g_val = next_g_val;
            h_val = std::max(f_val, g_val);

            // Handle event type
            if (type == 0) f_slope += delta;
            else if (type == 1) g_slope += delta;
            else if (type == -1) h.base_value = h_val;  // Record value at 0

            // Calculate new slope for max function
            double new_h_slope = (f_val > g_val) ? f_slope :
                (g_val > f_val) ? g_slope :
                std::max(f_slope, g_slope);

            // Add breakpoint if slope changes
            if (new_h_slope != h_slope) {
                double slope_delta = new_h_slope - h_slope;
                if (slope_delta > 0) {
                    h.breakpoints.push_back({ cur_x, slope_delta });
                }
                h_slope = new_h_slope;
            }
        }

        // Set final values for h
        if (h.breakpoints.empty()) {
            h.left_slope = init_h_slope;
            h.base_value = init_h_val - init_h_slope * x0;
        }
        else {
            h.left_slope = init_h_slope;
            if (std::isnan(h.base_value)) {
                // Compute base_value by integrating from x0 to 0
                double integral = init_h_slope * (0.0 - x0);
                for (const auto& bp : h.breakpoints) {
                    if (bp.first < 0) integral += bp.second * (0.0 - bp.first);
                }
                h.base_value = init_h_val + integral;
            }
        }

        // Sort breakpoints (should already be sorted, but ensure)
        std::sort(h.breakpoints.begin(), h.breakpoints.end());
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
        int t;
        cin >> t;

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
        cout << ans << " ";
    }

    //rep(i, 36)
    //{
    //    cout << fn[i].breakpoints.size() << "\n";
    //}

    return 0;
}
