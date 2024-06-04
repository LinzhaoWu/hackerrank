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
#include <unordered_map>
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
#ifndef OTHERS
int sherlockAndAnagrams(string s) {
    using CharArray = vector<uint8_t>;
    size_t ret(0);

    auto hash = [](const CharArray& arr){
        size_t code(0);
        for (const auto& e: arr) {
            code ^= e;
        }
        return std::hash<size_t>{}(code);
    };

    auto cmp = [](const CharArray& arr1, const CharArray& arr2){
        for (size_t i(0); i < arr1.size(); i++) {
            if (arr1[i] != arr2[i]) return false;
        }
        return true;
    };

    for (size_t sz(1); sz < s.size(); sz++) {
        unordered_map<CharArray, size_t, decltype(hash), decltype(cmp)> mp(s.size(), hash, cmp);
        for (size_t l(0); l < s.size(); l++) {
            CharArray arr(26);
            for (size_t r(0); r < sz; r++) {
                if (r + l >= s.size()) break;
                arr[s[r + l] - 'a']++;
            }
            mp[arr]++;
        }
        for (const auto& [_, n] : mp) {
            if (n >= 2) ret += (n * (n - 1)) / 2;
        }
    }
    return ret;
}

#else
int main() {
  int cases;
  scanf("%d", &cases);
  getchar();
  while (cases--) {
    unordered_map<string, int> mp;
    string s;
    getline(cin, s);
    int n = s.size();
    for (int len = 1; len < n; ++len) {
      for (int i = 0; i <= n - len; ++i) {
        string t = s.substr(i, len);
        sort(t.begin(), t.end());
        mp[t]++;
      }
    }
    long long ans = 0;
    for (auto t : mp) {
      ans += (long long)t.second * (t.second - 1) / 2;
    }
    printf("%lld\n", ans);
  }
  return 0;
}

#endif

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
