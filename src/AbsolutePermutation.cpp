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
 * Complete the 'absolutePermutation' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 */

vector<int> absolutePermutation(int n, int k) {
    vector<int> vRet;
    if (k == 0) {
        for (int i(1); i <= n; i++) {
            vRet.push_back(i);
        }
    } else if ((n % k) == 0 && (n / k) % 2 == 0) {
        for (int i(1); i <= n; i++) {
            if (((i - 1) / k) % 2 == 0) vRet.push_back(i + k);
            else vRet.push_back(i - k);
        }
    } else vRet.push_back(-1);
    return vRet;
}

int main()
{
    freopen("output.txt", "w", stdout);
    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string first_multiple_input_temp;
        getline(cin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int k = stoi(first_multiple_input[1]);

        vector<int> result = absolutePermutation(n, k);

        for (size_t i = 0; i < result.size(); i++) {
            cout << result[i];

            if (i != result.size() - 1) {
                cout << " ";
            }
        }

        cout << "\n";
    }

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
