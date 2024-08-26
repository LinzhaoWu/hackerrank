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

int steadyGene( std::string const & _gene)
{
    auto chrCounts = std::unordered_map<char, size_t>();
    for(auto const & chr : _gene) {
        ++chrCounts[chr];    
    }

    size_t minPossibleLength = 0;
    auto steadyCount = _gene.size() / 4;
    for(auto const &[_, count]: chrCounts) {
        if (count > steadyCount) {
            minPossibleLength += count - steadyCount;
        }
    } 

    auto minLength = _gene.size() - steadyCount;
    for(auto first = std::begin(_gene), last = first; 
        last != std::end(_gene);) {
        --chrCounts.at(*last++);
        while(std::all_of(std::begin(chrCounts), std::end(chrCounts),
                          [&](auto const & _chrCount){ return _chrCount.second <= steadyCount;})) {
            minLength = std::min(minLength, static_cast<size_t>( std::distance(first, last) + 1));
            if (minLength == minPossibleLength) return minLength;
            ++chrCounts.at(*first++);
        }
    }
    return minLength;
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
