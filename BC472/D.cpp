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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w, k;
    cin >> h >> w >> k;

    vector<string> g(h);
    for (int i = 0; i < h; i++)
    {
        cin >> g[i];
    }

    vector<bool> cs(w, true), rs(h, true);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (g[i][j] == '#')
            {
                cs[j] = false;
                rs[i] = false;
            }
        }
    }

    int MAX{h * w};
    vector<vector<int>> md(h, vector<int>(w, MAX));

    deque<pii> q;
    int res{};
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (rs[i] && cs[j])
            {
                q.push_back(pii{i, j});
                md[i][j] = 0;
                res++;
            }
        }
    }

    static vector<pii> dir{{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    while (q.size())
    {
        auto [x, y] = q.front();
        q.pop_front();
        int cmd = md[x][y];

        for (auto di : dir)
        {
            int xi = x + di.first;
            int yi = y + di.second;
            if (0 <= xi && xi < h && 0 <= yi && yi < w)
            {
                if (g[xi][yi] == '#')
                {
                    continue;
                }
                if (cmd + 1 < md[xi][yi] && cmd + 1 <= k)
                {
                    if (md[xi][yi] > k)
                    {
                        res++;
                    }

                    md[xi][yi] = cmd + 1;
                    q.emplace_back(xi, yi);
                }
            }
        }
    }

    cout << res << endl;
}

// int m = h + w - 1;
// vector<int> ud(m), dd(m);
// for (int i = 0; i < h; i++)
// {
//     for (int j = 0; j < w; j++)
//     {
//         if (rs[i] && cs[j])
//         {
//             // calculate dd
//             int dd_index{i - j};
//             if (dd_index < 0)
//             {
//                 dd_index = w - dd_index - 1;
//             }

//             int ud_index{i + j};

//             ud[ud_index]++;
//             dd[dd_index]++;
//         }
//     }
// }

// for (int i = 0; i < h; i++)
// {
//     for (int j = 0; j < w; j++)
//     {

//     }
// }
