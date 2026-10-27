#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                                                                                    \
    ios_base::sync_with_stdio(false);                                                              \
    cin.tie(NULL);

// int: 32 bits -+ 2**9
// long: 32 or 64 bits depending on the platform
// long long: 64 bits -+ 9**18
#define ll long long
#define vi vector<int>
#define vii vector<pair<int, int>>
#define pii pair<int, int>
#define rep(i, a, b) for (int i = a; i < b; ++i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define endl "\n"

// Constants
const int MOD = 1e9 + 7;
const int INF = 1e9;

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    s--;
    t--;

    vector<vector<int>> edges(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;

        edges[x].push_back(y);
    }

    vector<int> shortcuts(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (edges[i].size())
        {
            shortcuts[i] = *min_element(edges[i].begin(), edges[i].end());
        }
    }

    priority_queue<int, vector<int>, greater<int>> pq;
    pq.push(s);

    vector<int> distance(n, numeric_limits<int>::max());
    distance[s] = 0;

    // infinite loops
    // A and B can both be each other's shortcuts

    while (!pq.empty())
    {
        int current = pq.top();
        pq.pop();

        for (int neighbor : edges[current])
        {
            int next_distance;
            if (shortcuts[current] == neighbor)
            {
                next_distance = distance[current];
            }
            else
            {
                next_distance = distance[current] + 1;
            }

            if (next_distance < distance[neighbor])
            {
                distance[neighbor] = next_distance;
                pq.push(neighbor);
            }
        }
    }

    if (distance[t] == numeric_limits<int>::max())
    {
        cout << -1 << endl;
    }
    else
    {
        cout << distance[t] << endl;
    }
}
