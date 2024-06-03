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

/*
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int sherlockAndAnagrams(string s) {
    using CharArray = vector<uint8_t>;
    size_t ret(0);

    auto hash = [](const CharArray& arr){
        size_t ret = 0;
        for (const auto& e: arr) {
            ret ^= e;
        }
        return std::hash<size_t>{}(ret);
    };

    auto cmp = [](const CharArray& arr1, const CharArray& arr2){
        for (size_t i(0); i < arr1.size(); i++) {
            if (arr1[i] != arr2[i]) return false;
        }
        return true;
    };

    for (size_t sz(1); sz < s.size(); sz++) {
        unordered_map<CharArray, size_t, decltype(hash), decltype(cmp)> mp;
        for (size_t l(0); l < s.size() - sz; l++) {
            CharArray arr(26);
            for (size_t r(l); r < l + sz; r++) {
                arr[s[r] - 'a']++;
            }
            mp[arr]++;
        }
        for (const auto& [_, n] : mp) {
            if (n >= 2) ret += (n * n - 1) / 2;
        }
    }
    return ret;
}

int main()
{
    string q_temp;
    getline(cin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string s;
        getline(cin, s);

        int result = sherlockAndAnagrams(s);

        cout << result << "\n";
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
