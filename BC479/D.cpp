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
    cin >> n;

    int q;
    cin >> q;

    vector<ll> l(n), r(n);
    for (int i = 1; i < n; i++)
    {
        cin >> l[i];
    }

    for (int i = 0; i < n - 1; i++)
    {
        cin >> r[i];
    }

    // record the cheapest l_j out of all j > i
    // record the cheapest r_j out of all j < i
    vector<ll> ml(n), mr(n);

    ml[n - 1] = numeric_limits<ll>::max();
    for (int i = n - 2; i >= 0; i--)
    {
        ml[i] = min(ml[i + 1], l[i + 1]);
    }

    mr[0] = numeric_limits<ll>::max();
    for (int i = 1; i < n; i++)
    {
        mr[i] = min(mr[i - 1], r[i - 1]);
    }

    while (q--)
    {
        int s, t;
        cin >> s >> t;
        s--;
        t--;

        ll res{std::numeric_limits<ll>::max()};
        if (s < t)
        {
            // go towards the right
            // 1. can go left then right
            // 2. can go directly towards the right

            res = min(res, r[s]);
            if (s != 0)
            {
                res = min(res, l[s] + mr[s]);
            }
        }
        else
        {
            // 1. go directly to the left
            // 2. go to the right then backtrack

            res = min(res, l[s]);
            if (s != n - 1)
            {
                res = min(res, r[s] + ml[s]);
            }
        }

        cout << res << endl;
    }
}
