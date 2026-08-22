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

vector<int> fr, fc;
void update(vector<int> &fenwick, int i, int delta)
{
    i++;
    int n = fenwick.size();
    while (i < n)
    {
        fenwick[i] += delta;
        i += (i & -i);
    }
}

int query(vector<int> &fenwick, int a, int b)
{
    int res = 0;
    b += 1;
    while (b > 0)
    {
        res += fenwick[b];
        b -= (b & -b);
    }

    while (a > 0)
    {
        res -= fenwick[a];
        a -= (a & -a);
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    fr.resize(q + 1);
    fc.resize(q + 1);
    vector<int> ct(n, -1), rt(n, -1); // column time, row time

    ll res = 0;
    for (int t = 0; t < q; t++)
    {
        int query_type;
        cin >> query_type;

        if (query_type == 1)
        {
            int row;
            cin >> row;
            row--;

            // color the row black
            // we wish to know how many columns have been colored white
            // since the last time we colored this row black

            if (rt[row] != -1)
            {
                // how many distinct columns have we colored white since
                // time rt[row] to current time t
                res += query(fc, rt[row], t);
                update(fr, rt[row], -1);
                update(fr, t, 1);
                rt[row] = t;
            }
            else
            {
                // we have yet to color this row
                res += n;
                rt[row] = t;
                update(fr, t, 1);
            }
        }
        else
        {
            int col;
            cin >> col;
            col--;

            res -= query(fr, max(ct[col], 0), t);
            if (ct[col] != -1)
            {
                update(fc, ct[col], -1);
            }
            update(fc, t, 1);
            ct[col] = t;
        }

        cout << res << endl;
    }
}
