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
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pair<ll, ll>> t(n);
    vector<ll> lt(n);
    multiset<ll> heights;
    ll H = 0;
    for (int i = 0; i < n; i++)
    {
        ll h, l;
        cin >> h >> l;
        H = max(H, h);
        t[i] = pair<ll, ll>(h, l);
        heights.insert(h);
        lt[i] = l;
    }

    // sort by l
    sort(t.begin(), t.end(), [&](const auto &a, const auto &b) { return a.second < b.second; });
    sort(lt.begin(), lt.end());
    // m[i]: maximum height among the Takahashi if the 0, ..., ith Takahashi leave
    vector<ll> m(n);
    for (int i = 0; i < n; i++)
    {
        heights.erase(heights.find(t[i].first));
        if (heights.size())
        {
            m[i] = *heights.rbegin();
        }
        else
        {
            m[i] = 0;
        }
    }

    int q;
    cin >> q;
    while (q--)
    {
        ll t;
        cin >> t;

        int j = upper_bound(lt.begin(), lt.end(), t) - lt.begin();
        j--;

        if (j < 0)
        {
            cout << H << endl;
        }
        else
        {
            cout << m[j] << endl;
        }
    }
}
