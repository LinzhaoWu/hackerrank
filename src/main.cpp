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
#ifdef FIRST_TRY
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

#elif defined (DEAD_END_TRIAL)

int twoPluses(vector<string> grid) {
    const int iRowSize = static_cast<int>(grid.size());
    const int iColSize = static_cast<int>(grid.front().size());

    // Construct horizontal continuous good number matrix
    vector vvHorz(iRowSize, vector<int>(iColSize));
    for (int iRow(0); iRow < iRowSize; iRow++) {
        int iRepeats(0);
        vector<int> vForword(iColSize);
        for (int iCol(0); iCol < iColSize; iCol++) {
            if (grid[iRow][iCol] == 'G') ++iRepeats;
            else iRepeats = 0;
            vForword[iCol] = iRepeats;
        }

        iRepeats = 0;
        vector<int> vBackword(iColSize);
        for (int iCol(iColSize - 1); iCol >= 0; iCol--) {
            if (grid[iRow][iCol] == 'G') ++iRepeats;
            else iRepeats = 0;
            vBackword[iCol] = iRepeats;
        }

        for (int iCol(0); iCol < iColSize; iCol++) {
            vvHorz[iRow][iCol] = min(vForword[iCol], vBackword[iCol]);
        }
    }

    // Construct vertical continuous good number matrix
    vector vvVert(iRowSize, vector<int>(iColSize));
    for (int iCol(0); iCol < iColSize; iCol++) {
        int iRepeats(0);
        vector<int> vDownword(iRowSize);
        for (int iRow(0); iRow < iRowSize; iRow++) {
            if (grid[iRow][iCol] == 'G') ++iRepeats;
            else iRepeats = 0;
            vDownword[iRow] = iRepeats;
        }

        iRepeats = 0;
        vector<int> vUpword(iRowSize);
        for (int iRow(iRowSize - 1); iRow >= 0; iRow--) {
            if (grid[iRow][iCol] == 'G') ++iRepeats;
            else iRepeats = 0;
            vUpword[iRow] = iRepeats;
        }

        for (int iRow(0); iRow < iRowSize; iRow++) {
            vvVert[iRow][iCol] = min(vDownword[iRow], vUpword[iRow]);
        }
    }

    // Construct cross good number matrix
    vector vvCros(iRowSize, vector<int>(iColSize));
    for (int iRow(0); iRow < iRowSize; iRow++) {
        for (int iCol(0); iCol < iColSize; iCol++) {
            vvCros[iRow][iCol] = min(vvHorz[iRow][iCol], vvVert[iRow][iCol]);
        }
    }

    auto IsPeak = [&vvCros, iRowSize, iColSize](int r, int c){
        if (r < 1 || r == iRowSize - 1 || c < 0 || c == iColSize - 1) return false;
        if (vvCros[r][c] < vvCros[r - 1][c]) return false;
        if (vvCros[r][c] < vvCros[r + 1][c]) return false;
        if (vvCros[r][c] < vvCros[r][c - 1]) return false;
        if (vvCros[r][c] < vvCros[r][c + 1]) return false;

        return true;
    };

    // Validate crests to prevent overlaping
    vector vvMatrix(iRowSize, vector<int>(iColSize, 0));
    for (int iRow(0); iRow < iRowSize; iRow++) {
        for (int iCol(0); iCol < iColSize; iCol++) {
            const int iCur = vvCros[iRow][iCol];
            if (IsPeak(iRow, iCol)) {
                bool bPass(false);
                for (int r(iRow - iCur + 1); r < iRow + iCur; r++) { // See if intersected vertically
                    if (vvMatrix[r][iCol] >= iCur) { // check if larger value exists
                        bPass = true;
                        break;
                    }
                }
                if (bPass) continue; // if it exists, failed checking

                for (int c(iCol - iCur + 1); c < iCol + iCur; c++) { // See if intersected horizontally
                    if (vvMatrix[iRow][c] >= iCur) { // if value larger exists
                        bPass = true;
                        break;
                    }
                }
                if (bPass) continue; // if it exists, failed checking

                // No intersection
                for (int r(iRow - iCur + 1); r < iRow + iCur; r++) {
            }
        }
    }
}
#else
struct CrossesFound {
    bool isAllset() { return getSetCnt() == 2; }

    int getSetCnt() {
        int iRet(0);
        iRet += (i1st > 0)? 1 : 0;
        iRet += (i2nd > 0)? 1 : 0;
        return iRet;
    }
    bool toContinue() {
        if (i1st == 0 && i2nd == 0) return false;
        if (i1st == -1 && i2nd == -1) return false;
        if (i1st == 1 && i2nd == 1) return false;
        return true;
    }

    int i1st = -1;
    int i1stRow = -1;
    int i1stCol = -1;

    int i2nd = -1;
};

CrossesFound findTwoCrosses(vector<string> grid, CrossesFound cfLast)
{
    const int iRowSize = static_cast<int>(grid.size());
    const int iColSize = static_cast<int>(grid.front().size());

    CrossesFound cfRet;

    vector<int> vTest;
    int iMax = min(iRowSize, iColSize);
    if (iMax % 2 == 0) iMax -= 1;

    if (cfLast.i1st == -1) { // first time running, construct full range
        for (int i(iMax); i > 0; i -= 2) {
            vTest.push_back(i);
        }
    } else {
        for (int i(iMax); i > 0; i -= 2) {
            if (i <= cfLast.i1st && i > cfLast.i2nd) vTest.push_back(i);
        }
    }

    for(auto& size : vTest) {
        if (size > iRowSize && size > iColSize) continue;

        auto isMatched = [&grid, size](int iRow, int iCol){
            // Firstly, compare horizontal spread arm
            for (int c(0); c < size; c++) {
                if (grid[size / 2 + iRow][c + iCol] != 'G') return false;
            }
            // Then, compare vertical body
            for (int r(0); r < size; r++) {
                if (grid[r + iRow][size / 2 + iCol] != 'G') return false;
            }

            return true;
        };

        auto clearMatched = [&grid, size](int iRow, int iCol){
            for (int c(0); c < size; c++) {
                grid[size / 2 + iRow][c + iCol] = 'g';
            }
            for (int r(0); r < size; r++) {
                grid[r + iRow][size / 2 + iCol] = 'g';
            }
        };

        for (int iRow(0); iRow <= iRowSize - size; iRow++) {
            for (int iCol(0); iCol <= iColSize - size; iCol++) {
                if (cfLast.i1st == size) {
                    if (iRow < cfLast.i1stRow) continue;
                    else if (iRow == cfLast.i1stRow && iCol <= cfLast.i1stCol) continue;
                } 

                if (isMatched(iRow, iCol)) {
                    if (cfRet.i1st == -1) {
                        cfRet.i1st = size;
                        cfRet.i1stRow = iRow;
                        cfRet.i1stCol = iCol;
                    } else {
                        cfRet.i2nd = size;
                    }

                    clearMatched(iRow, iCol);

                    if (cfRet.isAllset()) 
                        return cfRet;

                    iCol += size - 1;
                }
            }
        }
    }

    if (cfRet.getSetCnt() == 1) {
        cfRet.i1st = 1;
        cfRet.i2nd = 1;
    } else {
        cfRet.i1st = 0;
        cfRet.i2nd = 0;
    }

    return cfRet; // the set size can only be 0 reaching here
}

int twoPluses(vector<string> grid) {
    int iRet(0);
    CrossesFound cf;

    auto getResult = [](auto cf) {
        return (cf.i1st * 2 - 1) * (cf.i2nd * 2 - 1);
    };

    cf = findTwoCrosses(grid, cf);
    iRet = getResult(cf);
    while (cf.toContinue()) {
        cf = findTwoCrosses(grid, cf);
        iRet = max(iRet, getResult(cf));
    }
    return iRet;
}
#endif

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
