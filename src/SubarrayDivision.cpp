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
 * Complete the 'birthday' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY s
 *  2. INTEGER d
 *  3. INTEGER m
 */

int birthday(vector<int> s, int d, int m) {
    if (s.size() < m) return 0;

    int sum = std::accumulate(s.begin(), s.begin() + m, 0);
    int ret = (sum == d)? 1 : 0;

    for (int r(m), l(0); r < s.size(); r++, l++) {
        sum = sum - s[l] + s[r];
        if (sum == d) ret++;
    }

    return ret;
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(((n_temp)));

    string s_temp_temp;
    getline(cin, s_temp_temp);

    vector<string> s_temp = split((s_temp_temp));

    vector<int> s(n);

    for (int i = 0; i < n; i++) {
        int s_item = stoi(s_temp[i]);

        s[i] = s_item;
    }

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split((first_multiple_input_temp));

    int d = stoi(first_multiple_input[0]);

    int m = stoi(first_multiple_input[1]);

    int result = birthday(s, d, m);

    cout << result << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), (isspace))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), (isspace)).base(),
        s.end()
    );

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
