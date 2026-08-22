#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    long long d;
    cin >> n >> d;

    vector<long long> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // for each index r, we want the lowest value of l such that [l ... r]
    // suppose current window is sparse
    // there are at most two values we need to avoid when adding in a new value
    // need the largest index of the maximal element lo such that lo <= a[r]
    // need the largest index of the minimal element hi such that hi >= a[r]
    // can use a multiset to represent the window

    multiset<pair<long long, int>> wi;
    int l = 0;
    long long res = 0;

    for (int i = 0; i < n; i++)
    {
        auto hi_it = wi.lower_bound({a[i], -1});

        if (hi_it != wi.begin())
        {
            auto lo_it = prev(hi_it);
            if (a[i] - lo_it->first < d)
            {
                while (l <= lo_it->second)
                {
                    wi.erase({a[l], l});
                    l++;
                }
            }
        }

        hi_it = wi.lower_bound({a[i], -1});

        if (hi_it != wi.end())
        {
            if (hi_it->first - a[i] < d)
            {
                while (l <= hi_it->second)
                {
                    wi.erase({a[l], l});
                    l++;
                }
            }
        }

        wi.insert({a[i], i});
        res += i - l + 1;
    }

    cout << res << endl;
}