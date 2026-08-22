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

    int n, k;
    cin >> n >> k;

    vector<pair<ll, ll>> cl;
    vector<ll> cc;
    for (int i = 0; i < n; i++)
    {
        ll l, r;
        cin >> l >> r;

        cl.emplace_back(l, r);
        cc.push_back(l);
    }

    ll MAX = 1e14;
    sort(cl.begin(), cl.end()); // sort by start time
    sort(cc.begin(), cc.end());
    cc.erase(unique(cc.begin(), cc.end()), cc.end());
    int m = cc.size();

    vector<ll> es(m, MAX); // e[i] is the earliest start time of all cloths
                           // that start on cc[i]
    ll MS = cc.back();
    for (int i = 0; i < n; i++)
    {
        int j = lower_bound(cc.begin(), cc.end(), cl[i].first) - cc.begin();
        es[j] = min(es[j], cl[i].second);
    }
    for (int i = m - 2; i >= 0; i--)
    {
        es[i] = min(es[i], es[i + 1]);
    }

    ll left = 0, right = 1e9;
    while (left < right)
    {
        ll mid = (left + right + 1) / 2;
        // determine if mid is a valid gap
        ll st = 0;
        bool valid = true;
        for (int i = 0; i < k; i++)
        {
            if (st > MS)
            {
                valid = false;
                break;
            }
            int j = lower_bound(cc.begin(), cc.end(), st) - cc.begin();
            st = es[j] + mid;
        }

        if (valid)
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    if (left == 0)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << left << endl;
    }
}
