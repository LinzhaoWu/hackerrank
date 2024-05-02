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

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'surfaceArea' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY A as parameter.
 */

int surfaceArea(vector<vector<int>> A) {
    const int arTop = A.front().size() * A.size();

    vector<int> vMaxC;
    vector<int> vMaxR;

    for (int i(0); i < A.size(); i++) {
        int iSide = 0;
        int iLast = 0;
        for (int j(0); j < A.front().size(); j++) {
            const int iCur = A[i][j];
            if (iCur > iLast) {
                iSide += iCur - iLast;
            }
            iLast = iCur;
        }
        vMaxR.push_back(iSide);
    }

    for (int j(0); j < A.front().size(); j++) {
        int iSide = 0;
        int iLast = 0;
        for (int i(0); i < A.size(); i++) {
            const int iCur = A[i][j];
            if (iCur > iLast) {
                iSide += iCur - iLast;
            }
            iLast = iCur;
        }
        vMaxC.push_back(iSide);
    }

    const int arSideR = accumulate(vMaxR.begin(), vMaxR.end(), 0);
    const int arSideC = accumulate(vMaxC.begin(), vMaxC.end(), 0);

    return arTop * 2 + arSideR * 2 + arSideC * 2;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int H = stoi(first_multiple_input[0]);

    int W = stoi(first_multiple_input[1]);

    vector<vector<int>> A(H);

    for (int i = 0; i < H; i++) {
        A[i].resize(W);

        string A_row_temp_temp;
        getline(cin, A_row_temp_temp);

        vector<string> A_row_temp = split(rtrim(A_row_temp_temp));

        for (int j = 0; j < W; j++) {
            int A_row_item = stoi(A_row_temp[j]);

            A[i][j] = A_row_item;
        }
    }

    int result = surfaceArea(A);

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
