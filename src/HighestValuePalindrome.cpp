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
 * Complete the 'highestValuePalindrome' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. STRING s
 *  2. INTEGER n
 *  3. INTEGER k
 */

string highestValuePalindrome(string s, int n, int k) {
    size_t uDiffCnt(0);
    size_t l(0), r(s.size() - 1);
    for (; l < r; l++, r--) {
        auto& left = s[l];
        auto& right = s[r];
        if (left != right) uDiffCnt++;
    }

    if (uDiffCnt > k) return string("-1");

    constexpr auto NINE = '9';
    l = 0; 
    r = s.size() - 1;
    for (; l < r; l++, r--) {
        auto& left = s[l];
        auto& right = s[r];
        if (left == right) {
            if (left == NINE) continue;

            if (k - uDiffCnt >= 2) {
                left = NINE;
                right = left;
                k -= 2;
            }
        } else {
            if (k - uDiffCnt >= 1) {
                if (left != NINE) {
                    left = NINE;
                    k--;
                }
                if (right != NINE) {
                    right = NINE;
                    k--;
                }
            } else {
                if (left > right) right = left;
                else left = right;

                k--;
            }
            uDiffCnt--;
        }
    }

    if (l == r && k > 0) s[l] = NINE;

    return s;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

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
