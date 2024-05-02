#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>
#include <iostream>
#include <queue>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <map>
#include <list>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'twoPluses' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY grid as parameter.
 */

int twoPluses(vector<string> grid) {
    pair<int, int> prLens{0, 0};

    auto AddLen = [&prLens](int len){
        if (len > prLens.first && len > prLens.second) {
            prLens.second = prLens.first; 
            prLens.first = len;
        } else if (len <= prLens.first && len > prLens.second) {
            prLens.second = len;
        }
    };

    #define INSIDE_LOOP(r, c)   {                   \
                if (grid[r][c] == 'G') iCurDis++;\
                else break;                         \
    }

    #define AFTER_LOOP() {                          \
            if (iCurDis == 1) {                     \
                AddLen(1);                          \
                continue;                           \
            }                                       \
            iMaxDis = min(iMaxDis, iCurDis);        \
                                                    \
            iCurDis = 1;                            \
    }

    const int iRowSize = static_cast<int>(grid.size());
    const int iColSize = static_cast<int>(grid.front().size());

    for (int iRow(0); iRow < iRowSize; iRow++) {
        for (int iCol(0); iCol < iColSize; iCol++) {
            if (grid[iRow][iCol] != 'G') continue;

            int iMaxDis = min(min(iRow, iRowSize - 1 - iRow), min(iCol, iColSize - 1 - iCol)) + 1;
            int iCurDis = iMaxDis;
            AFTER_LOOP();

            for (int r(iRow - 1); r > iRow - iMaxDis; r--) { // Up
                INSIDE_LOOP(r, iCol);
            }
            AFTER_LOOP();

            for (int r(iRow + 1); r < iRow + iMaxDis; r++) { // Down
                INSIDE_LOOP(r, iCol);
            }
            AFTER_LOOP();

            for (int c(iCol - 1); c > iCol - iMaxDis; c--) { // Left
                INSIDE_LOOP(iRow, c);
            }
            AFTER_LOOP();

            for (int c(iCol + 1); c < iCol + iMaxDis; c++) { // Right
                INSIDE_LOOP(iRow, c);
            }
            AFTER_LOOP();

            AddLen(iMaxDis);
        }
    }
    return (prLens.first * 4 - 3) * (prLens.second * 4 - 3);
}

int main()
{
    // freopen("output.txt", "w", stdout);
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    vector<string> grid(n);

    for (int i = 0; i < n; i++) {
        string grid_item;
        getline(cin, grid_item);

        grid[i] = grid_item;
    }

    int result = twoPluses(grid);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    return s;
}

string rtrim(const string &str) {
    string s(str);

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
