#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    int res = 0;
    while (m != 0)
    {
        int x = n % m;
        m = x;
        res++;
    }

    cout << res << endl;
}