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

/*
 * Complete the 'timeInWords' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts following parameters:
 *  1. INTEGER h
 *  2. INTEGER m
 */

string timeInWords(int h, int m) {
    constexpr array hours = {""sv,        "one"sv,       "two"sv,      "three"sv,
                            "four"sv,    "five"sv,      "six"sv,      "seven"sv,
                            "eight"sv,   "nine"sv,      "ten"sv,      "eleven"sv,
                            "twelve"sv, "thirteen"sv};
    constexpr array minutes = {
        "zero"sv, "one"sv, "two"sv, "three"sv, "four"sv, "five"sv, "six"sv, "seven"sv, "eight"sv, "nine"sv,
        "ten"sv, "eleven"sv, "twelve"sv, "thirteen"sv, "fourteen"sv, "fifteen"sv, "sixteen"sv, "seventeen"sv, "eighteen"sv, "nineteen"sv,
        "twenty"sv, "twenty one"sv, "twenty two"sv, "twenty three"sv, "twenty four"sv, "twenty five"sv, "twenty six"sv, "twenty seven"sv, "twenty eight"sv, "twenty nine"sv,       
    };

    string sRet;
    if (m == 0) {
        sRet = string(hours[h]) + string(" o' clock"sv);
    } else if (m == 15) {
        sRet = string("quarter") + string(" past "sv) + string(hours[h]);
    } else if (m == 30) {
        sRet = string("half") + string(" past "sv) + string(hours[h]);
    } else if (m == 45) {
        sRet = string("quarter") + string(" to "sv) + string(hours[h + 1]);
    } else if (m == 1) {
        sRet = string(minutes[m]) + string(" minute past ") + string(hours[h]);
    } else if (m < 30) {
        sRet = string(minutes[m]) + string(" minutes past ") + string(hours[h]);
    } else {
        sRet = string(minutes[60 - m]) + string(" minutes to ") + string(hours[h + 1]);
    }
    return sRet;
}

int main()
{
    string h_temp;
    getline(cin, h_temp);

    int h = stoi(ltrim(rtrim(h_temp)));

    string m_temp;
    getline(cin, m_temp);

    int m = stoi(ltrim(rtrim(m_temp)));

    string result = timeInWords(h, m);

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
