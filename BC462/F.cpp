#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        string s;
        cin >> s;
        int k;
        cin >> k;

        int i = 0;
        int n = s.size();

        vector<vector<vector<int>>> b(3, vector<vector<int>>(3));

        while (i < n - 2)
        {
            int g = 0;
            if (s[i] == 'A')
            {
                g++;
            }
            if (s[i + 1] == 'B')
            {
                g++;
            }
            if (s[i + 2] == 'C')
            {
                g++;
            }

            if (g == 3)
            {
                i += 3;
                continue;
            }
        }

        // _ _ _
        // A _ _
        // _ B _
        // _ _ C
        // A B _
        // A _ C
        // _ B C
    }
}