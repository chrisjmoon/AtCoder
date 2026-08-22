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
template <typename T>
void print_vector(const std::vector<T> &vec)
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

void dfs(int current, int parent, vector<vector<int>> &edges, vector<int> &seen, vector<int> &history, bool &found)
{
    seen[current] = history.size();
    history.push_back(current);
    for (auto neighbor : edges[current])
    {
        if (neighbor == parent)
        {
            continue;
        }

        if (seen[neighbor] != -1)
        {
            // cycle detected; confirm that it is odd
            int cycle_length = history.size() - seen[neighbor];
            if (cycle_length % 2 == 1)
            {
                history.push_back(neighbor);
                found = true;
                return;
            }
        }
        else
        {

            dfs(neighbor, current, edges, seen, history, found);
            if (found)
            {
                return;
            }
        }
    }
    history.pop_back();
}

void handle_test_case()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    vector<int> seen(n, -1);
    vector<int> history;
    bool found{false};

    dfs(0, -1, edges, seen, history, found);

    if (!history.size())
    {
        cout << -1 << endl;
        return;
    }

    int cycle_root = history.back();

    auto it = find(history.begin(), history.end(), cycle_root);
    if (it == history.end())
    {
        cout << -1 << endl;
        return;
    }
    cout << (history.end() - it - 1) << endl;
    int index = it - history.begin();
    for (int i = index; i < history.size() - 1; i++)
    {
        cout << history[i] + 1 << " ";
    }
    cout << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--)
    {
        handle_test_case();
    }
}
