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
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(string gene) {
    map<char, uint32_t> mp;
    for (const auto& c : gene) {
        mp[c]++;
    }

    const size_t uBalance = gene.size() / 4;
    int iL(0);
    int iR(gene.size() - 1);
    while (iL < gene.size()) {
        auto& c = gene[iL];
        if (mp[c] < uBalance) {
            mp[c]++;
            iL++;
        } else break;
    }
    while (iR >= 0)
    {
        auto& c = gene[iR];
        if (mp[c] < uBalance) {
            mp[]
        }
    }
    
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    string gene;
    getline(cin, gene);

    int result = steadyGene(gene);

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
