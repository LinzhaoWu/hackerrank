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
 * Complete the 'matrixRotation' function below.
 *
 * The function accepts following parameters:
 *  1. 2D_INTEGER_ARRAY matrix
 *  2. INTEGER r
 */

void matrixRotation(vector<vector<int>> matrix, int r) {
    const int n = matrix.front().size();
    const int m = matrix.size();
    const int iMaxLists = (min(m, n) + 1) / 2;
    auto mtxOutput = matrix;

    vector<list<pair<int, int>>> vLists(iMaxLists);
    for (int iList(0); iList < iMaxLists; iList++) {
        auto& curList = vLists[iList];
        for (int i = n - 2 - iList; i >= iList; i--) {
            curList.push_back({iList, i});
        }
        for (int i = 1 + iList; i <= m - 1 - iList; i++) {
            curList.push_back({i, iList});
        }
        for (int i = 1 + iList; i <= n - 1 - iList; i++) {
            curList.push_back({m - 1 - iList, i});
        }
        for (int i = m - 2 - iList; i >= iList; i--) {
            curList.push_back({i, n - 1 - iList});
        }
    }

    for (int iList(0); iList < iMaxLists; iList++) {
        auto& curList = vLists[iList];
        const int32_t steps = -(r % curList.size());

        auto it = curList.end();
        advance(it, steps);

        remove_reference<decltype(curList)>::type cut;
        cut.splice(cut.begin(), curList, it, curList.end());
        curList.splice(curList.begin(), cut);
    }

    for (int iList(0); iList < iMaxLists; iList++) {
        auto& curList = vLists[iList];
        auto it = curList.begin();

        for (int i = n - 2 - iList; i >= iList; i--, it++) {
            mtxOutput[iList][i] = matrix[it->first][it->second];
        }
        for (int i = 1 + iList; i <= m - 1 - iList; i++, it++) {
            mtxOutput[i][iList] = matrix[it->first][it->second];
        }
        for (int i = 1 + iList; i <= n - 1 - iList; i++, it++) {
            mtxOutput[m - 1 - iList][i] = matrix[it->first][it->second];
        }
        for (int i = m - 2 - iList; i >= iList; i--, it++) {
            mtxOutput[i][n - 1 - iList] = matrix[it->first][it->second];
        }
    }

    for (int i(0); i < m; i++) {
        for (int j(0); j < n; j++) {
            cout << mtxOutput[i][j] << " ";
        }
        cout << "\r\n";
    }
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);

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
