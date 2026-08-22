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

// Write your solution here
// C++23 using GCC 14.2
// Debug with std::cerr or std::clog.
// !!! IMPORTANT !!!
// 99% of headers are pre-compiled for you server-side.
// If your submission fails to compile due to a missing header, add it to your submission.

std::vector<std::vector<char>> rotateTheBox(std::vector<std::vector<char>> box)
{

    int H = box.size();
    int W = box[0].size();

    for (int i = 0; i < H; i++)
    {
        int emptyCount = 0;
        int stoneCount = 0;
        vector<char> newRow;
        for (int j = W - 1; j >= 0; j--)
        {
            if (box[i][j] == '*')
            {
                for (int k = 0; k < stoneCount; k++)
                {
                    newRow.push_back('#');
                }
                for (int k = 0; k < emptyCount; k++)
                {
                    newRow.push_back('.');
                }

                emptyCount = 0;
                stoneCount = 0;
            }
            else
            {
                emptyCount += (box[i][j] == '.');
                stoneCount += (box[i][j] == '#');
            }
        }
        for (int k = 0; k < stoneCount; k++)
        {
            newRow.push_back('#');
        }
        for (int k = 0; k < emptyCount; k++)
        {
            newRow.push_back('.');
        }

        for (auto val : newRow)
        {
            cout << val << " ";
        }

        box[i] = newRow;
    }

    vector<vector<char>> flipped;

    for (int i = W - 1; i >= 0; i--)
    {
        vector<char> turnedColumn;
        for (int j = H - 1; j >= 0; j--)
        {
            turnedColumn.push_back(box[j][i]);
        }

        flipped.push_back(turnedColumn);
    }

    cout << "???" << endl;

    for (auto row : flipped)
    {
        for (auto val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return flipped;
}

int main()
{
    std::vector<std::vector<char>> a = rotateTheBox({{'#', '.', '#'}});
    return 0;
}