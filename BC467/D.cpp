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

pair<ll, ll> midpoint(ll x1, ll y1, ll x2, ll y2)
{
    return pair<ll, ll>(x1 + x2, y1 + y2);
}

pair<ll, ll> direction_vector(ll x1, ll y1, ll x2, ll y2)
{
    return pair<ll, ll>(x1 - x2, y1 - y2);
}

pair<ll, ll> perpendicular_vector(ll x1, ll y1, ll x2, ll y2)
{
    return pair<ll, ll>(-(y2 - y1), x2 - x1);
}

__int128 cross_product(ll x1, ll y1, ll x2, ll y2)
{
    return (__int128)x1 * y2 - (__int128)x2 * y1;
}

bool test_case(ll px, ll py, ll qx, ll qy, ll rx, ll ry, ll sx, ll sy)
{
    pair<ll, ll> m1 = midpoint(px, py, qx, qy);
    pair<ll, ll> d1 = perpendicular_vector(px, py, qx, qy);

    pair<ll, ll> m2 = midpoint(rx, ry, sx, sy);
    pair<ll, ll> d2 = perpendicular_vector(rx, ry, sx, sy);
    __int128 c = cross_product(d1.first, d1.second, d2.first, d2.second);

    if (c == 0)
    {
        // lines are parallel
        pair<ll, ll> d3 = direction_vector(m1.first, m1.second, m2.first, m2.second);
        // check whether the vector between the midpoints is parallel to d1, d2

        __int128 c_ = cross_product(d1.first, d1.second, d3.first, d3.second);
        if (c_ == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return true;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        ll px, py, qx, qy, rx, ry, sx, sy;
        cin >> px >> py >> qx >> qy >> rx >> ry >> sx >> sy;

        if (test_case(px, py, qx, qy, rx, ry, sx, sy))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}
