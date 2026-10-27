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

using entry = pair<int, pair<int, int>>;

vector<int> tree;

void update(int x, int v)
{
    x++;
    int n = tree.size();
    while (x < n)
    {
        tree[x] += v;
        x += (x & -x);
    }
}

int query(int x)
{
    x++;
    int res{0};
    while (x > 0)
    {
        res += tree[x];
        x -= (x & -x);
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // sort by X
    // for each X
    //   coalesce intersecting intervals into longer ranges
    //   for each range, range update the segment tree

    int n, q;
    cin >> n >> q;

    tree.resize(n + 2);
    vector<entry> entries(q);

    vector<int> x_values;
    for (int i = 0; i < q; i++)
    {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        r--;
        entries[i] = entry(x, pair<int, int>(l, r));
        x_values.push_back(x);
    }

    sort(x_values.begin(), x_values.end());
    x_values.erase(unique(x_values.begin(), x_values.end()), x_values.end());

    vector<vector<pair<int, int>>> intervals(x_values.size());

    for (const entry &e : entries)
    {
        int x_index = lower_bound(x_values.begin(), x_values.end(), e.first) - x_values.begin();
        intervals[x_index].push_back(e.second);
    }

    for (int i = 0; i < x_values.size(); i++)
    {
        sort(intervals[i].begin(), intervals[i].end());

        int current_left = -1;
        int current_right = -1;
        for (const auto &[left, right] : intervals[i])
        {
            if (left <= current_right)
            {
                current_right = max(current_right, right);
            }
            else
            {
                if (current_left != -1)
                {
                    update(current_left, 1);
                    update(current_right + 1, -1);
                }

                current_left = left;
                current_right = right;
            }
        }

        if (current_left != -1)
        {
            update(current_left, 1);
            update(current_right + 1, -1);
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << query(i) << " ";
    }
    cout << endl;
}
