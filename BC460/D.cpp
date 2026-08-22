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
long long modpow(long long x, long long y, long long mod)
{
    long long res = 1 % mod;
    x %= mod;

    while (y > 0)
    {
        if (y & 1)
        {
            res = (__int128)res * x % mod;
        }

        x = (__int128)x * x % mod;
        y >>= 1;
    }

    return res;
}

long long phi(long long n)
{
    long long res = n;

    for (long long p = 2; p * p <= n; p++)
    {
        if (n % p == 0)
        {
            while (n % p == 0)
            {
                n /= p;
            }

            res -= res / p;
        }
    }

    if (n > 1)
    {
        res -= res / n;
    }

    return res;
}

vector<pair<int, int>> dir = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
vector<vector<int>> adj;

string operation(const string &grid)
{
    string ng = string(grid.size(), '.');
    for (int i = 0; i < grid.size(); i++)
    {
        if (grid[i] == '#')
        {
            continue;
        }
        for (auto neighbor : adj[i])
        {
            if (grid[neighbor] == '#')
            {
                ng[i] = '#';
                break;
            }
        }
    }

    return ng;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w;
    cin >> h >> w;

    vector<string> grid(h);
    for (int i = 0; i < h; i++)
    {
        cin >> grid[i];
    }

    // compute the distance of each cell to the nearest white and black cell
    int INF = 1e7;
    vector<vector<int>> db(h, vector<int>(w, INF)), dw(h, vector<int>(w, INF));

    vector<vector<bool>> seen(h, vector<bool>(w));
    deque<pair<int, int>> q;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (grid[i][j] == '.')
            {
                q.emplace_back(i, j);
                seen[i][j] = true;
                dw[i][j] = 0;
            }
        }
    }

    while (q.size())
    {
        auto [ci, cj] = q.front();
        q.pop_front();

        for (auto [di, dj] : dir)
        {
            int ni = ci + di;
            int nj = cj + dj;
            if (0 <= ni && ni < h && 0 <= nj && nj < w)
            {
                if (!seen[ni][nj] && grid[ni][nj] == '#')
                {
                    dw[ni][nj] = dw[ci][cj] + 1;
                    seen[ni][nj] = true;
                    q.emplace_back(ni, nj);
                }
            }
        }
    }

    seen.assign(h, vector<bool>(w, false));
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (grid[i][j] == '#')
            {
                seen[i][j] = true;
                q.emplace_back(i, j);
                db[i][j] = 0;
            }
        }
    }

    while (q.size())
    {
        auto [ci, cj] = q.front();
        q.pop_front();

        for (auto [di, dj] : dir)
        {
            int ni = ci + di;
            int nj = cj + dj;
            if (0 <= ni && ni < h && 0 <= nj && nj < w)
            {
                if (!seen[ni][nj] && grid[ni][nj] == '.')
                {
                    db[ni][nj] = db[ci][cj] + 1;
                    seen[ni][nj] = true;
                    q.emplace_back(ni, nj);
                }
            }
        }
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (grid[i][j] == '.')
            {
                if (db[i][j] != INF && db[i][j] % 2 == 0)
                {
                    cout << "#";
                }
                else
                {
                    cout << ".";
                }
            }
            else
            {
                if (dw[i][j] != INF && dw[i][j] % 2 == 1)
                {
                    cout << "#";
                }
                else
                {
                    cout << ".";
                }
            }
        }
        cout << endl;
    }
}
