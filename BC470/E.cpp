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

// determine the number of expected pairs one would win by
// end of game from the current state
// c0 is the number of pairs for which both cards are in unknown positions
// c1 is the number of poirs for which exactly one card is in an unknown position
// the number of unseen cards is 2c0 + c1

vector<vector<vector<double>>> memo;

double expected_pairs(int l, int c0, int c1)
{
    // unknown cards: m = 2c0 + c1
    // known cards: c1
    // first we pick an unknown card
    // case 1: the card we pick has a known counterpart (c1/m)
    // case 2: the card we pick has no known counterpart; the second card we pick
    //   matches
    // case 3: the card we pick has no known counterpart; the second card we pick
    //   has no known counterpart
    // case 4: the card we pick has no known counterpart; the second card we pick
    //   has a known counterpart; assuming l > 1, we have enough life to
    //   match the second card to its counterpart immediately after

    if (memo[l][c0][c1] != -1)
    {
        return memo[l][c0][c1];
    }

    double m = 2 * c0 + c1;
    if (l == 0 || m == 0)
    {
        return 0;
    }

    double res{};

    double p1 = c1 / m;
    if (c1 > 0)
    {
        res += p1 * (1 + expected_pairs(l, c0, c1 - 1));
    }

    if (m > 1)
    {
        double p2 = (2 * c0 / m) * (1 / (m - 1));
        double p3 = (2 * c0 / m) * ((2 * c0 - 2) / (m - 1));
        double p4 = (2 * c0 / m) * (c1 / (m - 1));

        if (c0 > 0)
        {
            res += p2 * (1 + expected_pairs(l, c0 - 1, c1));
        }
        if (c0 >= 2)
        {
            res += p3 * expected_pairs(l - 1, c0 - 2, c1 + 2);
        }
        if (l > 1 && c0 > 0)
        {
            // costs us a life to pair the known counterpart after missing
            res += p4 * (1 + expected_pairs(l - 1, c0 - 1, c1));
        }
    }

    memo[l][c0][c1] = res;

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, l;
    cin >> n >> l;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    memo.resize(l + 1, vector<vector<double>>(n + 1, vector<double>(n + 1, -1)));

    // always flip an unseen card first
    // in either strategy A or B, you flip an unseen card
    // so might as well flip the unseen card first
    // based on the result of this flip, the strategy becomes forced

    double x = expected_pairs(l, n, 0);

    int value_sum = 0;
    for (auto v : a)
    {
        value_sum += v;
    }

    double average_value = value_sum / static_cast<double>(n);

    cout << setprecision(10);
    cout << (x * average_value) << endl;
}
