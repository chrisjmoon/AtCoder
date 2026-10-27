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

ll global_count{};
vector<vector<int>> e;
vector<ll> res;
vector<int> depth;

void count_subnodes(vector<int> &subnodes, int parent, int current)
{
    if (parent != -1)
    {
        depth[current] = depth[parent] + 1;
    }

    for (auto neighbor : e[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        count_subnodes(subnodes, current, neighbor);
        subnodes[current] += subnodes[neighbor];
    }
    subnodes[current]++; // add self
}

void propagate(int parent, int current, ll update, vector<ll> &subtree_update)
{
    update += subtree_update[current];
    res[current] = global_count + update;

    for (auto neighbor : e[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        propagate(current, neighbor, update, subtree_update);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    e.resize(n);
    res.resize(n);
    depth.resize(n, 0);

    vector<pii> edges;
    for (int i = 0; i < n - 1; i++)
    {
        int s, t;
        cin >> s >> t;
        s--;
        t--;

        e[s].push_back(t);
        e[t].push_back(s);

        edges.emplace_back(s, t);
    }

    // root the entire tree at 0 (arbitrary)
    // for each subtree root, record the local subtraction to propagate
    // for each subtree root, record the number of vertices in the subtree

    vector<ll> subtree_update(n);
    vector<int> subnodes(n);

    count_subnodes(subnodes, -1, 0);

    for (int i = 0; i < n - 1; i++)
    {
        // removing edge s, t
        auto [s, t] = edges[i];

        // determine which has greater depth
        // swap such that s is the subtree root
        if (depth[s] < depth[t])
        {
            swap(s, t);
        }

        int s_nodes = subnodes[s];

        if (s_nodes <= n / 2)
        {
            global_count += (i + 1);
            subtree_update[s] = -(i + 1);
        }
        else
        {
            subtree_update[s] = (i + 1);
        }
    }

    propagate(-1, 0, 0, subtree_update);

    for (int i = 0; i < n; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
}
