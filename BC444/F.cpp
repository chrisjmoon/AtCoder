#include <bits/stdc++.h>

using namespace std;
using pll = pair<long long, long long>;

long long count_good_fast(long long len, long long x, long long cap)
{
    if (len < x)
        return 0;

    map<long long, long long> cur;
    cur[len] = 1;

    long long good = 0;

    auto add_capped = [&](map<long long, long long> &mp, long long key, long long val)
    {
        if (val <= 0)
            return;
        mp[key] = min(cap, mp[key] + val);
    };

    while (!cur.empty() && good < cap)
    {
        map<long long, long long> nxt;

        for (auto [L, cnt] : cur)
        {
            cnt = min(cnt, cap - good);

            if (L < x)
            {
                continue;
            }
            else if (L / 2 < x)
            {
                good += cnt;
                good = min(good, cap);
            }
            else
            {
                add_capped(nxt, L / 2, cnt);
                add_capped(nxt, (L + 1) / 2, cnt);
            }

            if (good >= cap)
                return cap;
        }

        cur.swap(nxt);
    }

    return min(good, cap);
}

void test_case()
{
    int n;
    long long m;
    cin >> n >> m;

    vector<int> a(n);
    int MAX = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        MAX = max(MAX, a[i]);
    }
    sort(a.begin(), a.end());

    // potential median M
    // need at least half be greater than M

    int L = 1;
    int R = MAX;
    long long target = (n + m + 1) / 2;
    while (L < R)
    {
        int M = (L + R + 1) / 2;
        long long splits = 0;
        long long ig = 0;
        int index = lower_bound(a.begin(), a.end(), M) - a.begin();
        for (int i = index; i < n; i++)
        {
            long long c = count_good_fast(a[i], M, target);
            if (c > 0)
            {
                ig += 1;
                splits += c - 1;
            }

            if (ig + min(splits, m))
            {
                break;
            }
        }

        if (ig + min(splits, m) >= target)
        {
            L = M;
        }
        else
        {
            R = M - 1;
        }
    }

    cout << L << endl;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        test_case();
    }
}