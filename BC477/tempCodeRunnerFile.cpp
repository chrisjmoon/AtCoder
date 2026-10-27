#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define vii vector<pair<int, int>>
#define pii pair<int, int>
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define endl "\n"

const long long MOD = 998244353;

struct mint
{
    long long value;

    mint(long long value_ = 0)
    {
        value = value_ % MOD;
        if (value < 0)
        {
            value += MOD;
        }
    }

    mint &operator+=(const mint &other)
    {
        value = (value + other.value) % MOD;
        return *this;
    }

    mint &operator-=(const mint &other)
    {
        value = (value - other.value) % MOD;
        if (value < 0)
        {
            value += MOD;
        }
        return *this;
    }

    mint &operator*=(const mint &other)
    {
        value = (value * other.value) % MOD;
        return *this;
    }

    static mint modpow(mint base, long long exp)
    {
        mint res = 1;
        if (exp == 0)
        {
            return res;
        }

        while (exp > 0)
        {
            if (exp & 1)
            {
                res *= base;
                exp -= 1;
            }

            base *= base;
            exp >>= 1;
        }

        return res;
    }

    static mint inverse(mint a)
    {
        return modpow(a, MOD - 2);
    }

    mint &operator/=(const mint &other)
    {
        value = value * inverse(other).value % MOD;
        return *this;
    }

    friend mint operator+(mint a, mint const &b)
    {
        return a += b;
    }

    friend mint operator-(mint a, mint const &b)
    {
        return a -= b;
    }

    friend mint operator*(mint a, mint const &b)
    {
        return a *= b;
    }

    friend mint operator/(mint a, mint const &b)
    {
        return a /= b;
    }
};

// Utility functions
ll gcd(ll a, ll b)
{
    return b == 0 ? a : gcd(b, a % b);
}
ll lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

// print vector
template <typename T> void print_vector(const std::vector<T> &vec)
{
    for (const T &x : vec)
    {
        std::cout << x << " ";
    }
    std::cout << '\n';
}

// binary exponentiation
ll pow(ll x, ll y, ll MOD = 0)
{
    ll res = 1;
    while (y > 0)
    {
        if (y % 2)
        {
            res *= x;
            if (MOD != 0)
                res %= MOD;
            y -= 1;
        }
        else
        {
            x *= x;
            if (MOD != 0)
                x %= MOD;
            y /= 2;
        }
    }

    return res;
}

int digits(ll x)
{
    return to_string(x).size();
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int q;

    cin >> n >> q;

    // for each square, determine the last time it wasn't covered by a tile

    vector<vector<int>> off_times(n, vector<int>{0});
    vector<vector<pair<int, int>>> intervals(n);
    vector<bool> state(n, false); // all start off in the off state
    vector<int> color_times;
    vector<char> colors;

    for (int i = 1; i <= q; i++)
    {
        int query_type;
        cin >> query_type;

        if (query_type == 1)
        {
            int x;
            cin >> x;

            x--;
            if (!state[x])
            {
                intervals[x].emplace_back(off_times[x].back(), i);
            }
            else
            {
                off_times[x].push_back(i);
            }

            state[x] = !state[x];
        }
        else
        {
            char c;
            cin >> c;

            color_times.push_back(i);
            colors.push_back(c);
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (!state[i])
        {
            intervals[i].emplace_back(off_times[i].back(), q + 1);
        }

        // cout << "i: " << i << endl;

        char current_color{'a'};
        for (auto it = intervals[i].rbegin(); it != intervals[i].rend(); ++it)
        {
            auto interval = *it;
            int left = interval.first;
            int right = interval.second;

            // cout << "left, right: " << left << " " << right << endl;

            // determine the last coloring in this closed interval

            int ci =
                upper_bound(color_times.begin(), color_times.end(), right) - color_times.begin();
            if (ci == 0)
            {
                continue;
            }

            ci--;

            int color_time{color_times[ci]};
            if (left < color_time)
            {
                current_color = colors[ci];
                break;
            }
        }

        cout << current_color;
    }

    cout << endl;
}
