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
 * Complete the 'almostSorted' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 */

void almostSorted(vector<int> arr) 
{
    auto vSorted = arr;
    sort(vSorted.begin(), vSorted.end());

    vector<int> vIndex;
    for (int32_t i(0); i < (int32_t)vSorted.size(); i++) {
        if (vSorted[i] != arr[i]) vIndex.push_back(i);
    }

    if (vIndex.size() == 0) {
        cout << "yes\n";

    } else if (vIndex.size() == 1) {
        cout << "no\n";

    } else if (vIndex.size() == 2) {
        cout << "yes\nswap " << vIndex.front() + 1 << " " << vIndex.back() + 1 << "\n";

    } else {
        for (int32_t i(1); i < (int32_t)vIndex.size(); i++) {
            if (i == vIndex.size() / 2) continue;
            if (vIndex[i] != vIndex[i - 1] + 1) {
                cout << "no\r\n";
                return;
            }
        }
        for (int32_t i(1); i < (int32_t)vIndex.size(); i++) {
            if (arr[vIndex[i - 1]] < arr[vIndex[i]]) {
                cout << "no\r\n";
                return;
            }
        }
        cout << "yes\nreverse " << vIndex.front() + 1 << " " << vIndex.back() + 1 << "\n";
    }
}

// #define FILE_INPUT
int main()
{
    // freopen("output.txt", "w", stdout); // file output
    #ifdef FILE_INPUT
    ifstream inFile;
    inFile.open("input.txt");
    if (!inFile.is_open()) {
         std::cout << "failed to open file \n";
        return 0;
    }
    #endif

    string n_temp;
    #ifdef FILE_INPUT
    getline(inFile, n_temp);
    #else
    getline(cin, n_temp);
    #endif

    int n = stoi(ltrim(rtrim(n_temp)));

    string arr_temp_temp;
    #ifdef FILE_INPUT
    getline(inFile, arr_temp_temp);
    #else
    getline(cin, arr_temp_temp);
    #endif

    vector<string> arr_temp = split(rtrim(arr_temp_temp));

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        int arr_item = stoi(arr_temp[i]);

        arr[i] = arr_item;
    }

    almostSorted(arr);

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
