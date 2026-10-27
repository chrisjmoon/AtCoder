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

    int n, q;
    cin >> n >> q;

    vector<pair<int, int>> white_edges;
    vector<vector<int>> adj(n), rev(n);
    vector<bool> visited(n, false);
    vector<int> order;
    vector<int> component(n, -1);

    for (int i = 0; i < q; i++)
    {
        int edge_type, u, v;
        cin >> edge_type >> u >> v;
        u--;
        v--;

        if (edge_type == 1)
        {
            white_edges.emplace_back(u, v);
        }
        adj[u].push_back(v);
        rev[v].push_back(u);
    }

    auto dfs1 = [&](auto &&self, int u) -> void
    {
        visited[u] = true;
        for (int v : adj[u])
        {
            if (!visited[v])
            {
                self(self, v);
            }
        }

        order.push_back(u);
    };

    for (int u = 0; u < n; ++u)
    {
        if (!visited[u])
        {
            dfs1(dfs1, u);
        }
    }

    auto dfs2 = [&](auto &&self, int u, int id) -> void
    {
        component[u] = id;
        for (int v : rev[u])
        {
            if (component[v] == -1)
            {
                self(self, v, id);
            }
        }
    };

    reverse(order.begin(), order.end());

    int component_count = 0;
    for (int u : order)
    {
        if (component[u] == -1)
        {
            dfs2(dfs2, u, component_count++);
        }
    }

    // determine if white edges have a contradiction
    for (const auto &e : white_edges)
    {
        if (component[e.first] == component[e.second])
        {
            cout << "No" << endl;
            return 0;
        }
    }

    vector<vector<int>> ce(component_count);
    vector<int> in_degree(component_count);

    for (int i = 0; i < n; i++)
    {
        for (int j : adj[i])
        {
            int a = component[i];
            int b = component[j];

            if (a == b)
            {
                continue;
            }

            ce[a].push_back(b);
            in_degree[b]++;
        }
    }

    queue<int> tq;

    for (int c = 0; c < component_count; c++)
    {
        if (in_degree[c] == 0)
        {
            tq.push(c);
        }
    }

    int value{1};
    // holds the values we will assign to each component
    vector<int> cv(component_count);

    while (tq.size())
    {
        int c = tq.front();
        tq.pop();

        cv[c] = value++;

        for (auto neighbor : ce[c])
        {
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0)
            {
                tq.push(neighbor);
            }
        }
    }

    cout << "Yes" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << cv[component[i]] << " ";
    }
    cout << endl;
}
