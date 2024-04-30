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
#include <deque>
#include <iostream>
#include <vector>
#include <functional>
#include <numeric>
#include <map>
#include <list>

using namespace std;

/*
 * Complete the 'encryption' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string encryption(string s) {
    string sStriped;
    std::size_t posStart = 0;
    std::string_view svLine = s;
    const std::string_view svDelimiters = " ";
    std::size_t posEnd = svLine.find_first_of(svDelimiters, posStart);
    while (posEnd != std::string_view::npos) {
        sStriped.append(svLine.substr(posStart, posEnd - posStart));
        posStart = posEnd + 1;
        posEnd = svLine.find_first_of(svDelimiters, posStart);
    }
    sStriped.append(svLine.substr(posStart, svLine.size() - posStart));

    const int iL = sStriped.size();
    int iRow = floor(sqrt(iL));
    const int iColumn = ceil(sqrt(iL));
    if (iRow * iColumn < iL) iRow += 1;

    std::vector<std::vector<char>> mtx(iRow, std::vector<char>(iColumn, 0));
    int i(0);
    for (int r(0); r < iRow; r++) {
        for (int c(0); c < iColumn; c++) {
            if (i < sStriped.size()) mtx[r][c] = sStriped[i++];
        }
    }

    std::string sRet;
    for (int c(0); c < iColumn; c++) {
        for (int r(0); r < iRow; r++) {
            if (mtx[r][c] != 0) sRet.push_back(mtx[r][c]);
        }
        sRet.push_back(' ');
    }
    return sRet;
}

int main()
{
    string s;
    getline(cin, s);

    string result = encryption(s);

    cout << result << "\n";

    return 0;
}
