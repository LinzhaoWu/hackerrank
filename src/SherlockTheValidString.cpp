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


/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string isValid(string s) {
    constexpr auto sYes = "YES";
    constexpr auto sNo = "NO";
    unordered_map<char, uint32_t> umpChar2Num;
    for (const auto& c : s) {
        umpChar2Num[c]++;
    }

    map<uint32_t, uint32_t> umpNum2Cnt;
    for (const auto&[_, n] : umpChar2Num) {
        umpNum2Cnt[n]++;
    }

    if (umpNum2Cnt.size() == 1) return sYes;
    if (umpNum2Cnt.size() != 2) return sNo;
    const auto& prFront = *umpNum2Cnt.begin();
    const auto& prTail = *(++umpNum2Cnt.begin());
    if (prFront.first == 1 && prFront.second == 1) return sYes;

    if (prFront.first + 1 != prTail.first) return sNo;
    if (prTail.second != 1) return sNo;

    return sYes;
}

int main()
{
    string s;
    getline(cin, s);

    string result = isValid(s);

    cout << result << "\n";

    return 0;
}
