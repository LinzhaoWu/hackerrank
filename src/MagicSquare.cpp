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

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'formingMagicSquare' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY s as parameter.
 */

int formingMagicSquare(vector<vector<int>> s) {
    int magic_square[][3][3] = {{{6, 1, 8}, {7, 5, 3}, {2, 9, 4}},
                                {{8, 1, 6}, {3, 5, 7}, {4, 9, 2}},
                                {{6, 7, 2}, {1, 5, 9}, {8, 3, 4}},
                                {{8, 3, 4}, {1, 5, 9}, {6, 7, 2}},
                                {{2, 7, 6}, {9, 5, 1}, {4, 3, 8}},
                                {{4, 3, 8}, {9, 5, 1}, {2, 7, 6}},
                                {{2, 9, 4}, {7, 5, 3}, {6, 1, 8}},
                                {{4, 9, 2}, {3, 5, 7}, {8, 1, 6}}};

    int iMinCost = INT32_MAX;
    for (int i(0); i < sizeof(magic_square)/sizeof(magic_square[0]); i++) {
        int iSum(0);
        for (int j(0); j < 3; j++) {
            for (int k(0); k < 3; k++) {
                iSum += abs(magic_square[i][j][k] - s[j][k]);
            }
        }
        if (iSum < iMinCost) iMinCost = iSum;
    }
    return iMinCost;
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    vector<vector<int>> s(3);

    for (int i = 0; i < 3; i++) {
        s[i].resize(3);

        string s_row_temp_temp;
        getline(cin, s_row_temp_temp);

        vector<string> s_row_temp = split(rtrim(s_row_temp_temp));

        for (int j = 0; j < 3; j++) {
            int s_row_item = stoi(s_row_temp[j]);

            s[i][j] = s_row_item;
        }
    }

    int result = formingMagicSquare(s);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    // s.erase(
    //     s.begin(),
    //     find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    // );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    // s.erase(
    //     find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
    //     s.end()
    // );

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
