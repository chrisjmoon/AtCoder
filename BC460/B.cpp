#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        long long x1, y1, x2, y2, r1, r2;
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

        long double dx = (long double)(x1 - x2);
        long double dy = (long double)(y1 - y2);

        // distance between the centers
        long double dist = sqrt(dx * dx + dy * dy);

        if (max(r1, r2) <= dist + min(r1, r2) && dist <= r1 + r2)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }
}