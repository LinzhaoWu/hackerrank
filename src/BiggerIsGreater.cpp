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
 * Complete the 'biggerIsGreater' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING w as parameter.
 */

string biggerIsGreater(string w) {
    string svFail = "no answer";
    if (w.size() == 1) return svFail;

    int iCrest(w.size() - 1);
    for (; iCrest >= 1; iCrest--) { // Find last crest
        if (w[iCrest - 1] < w[iCrest]) {
            break;
        }
    }
    if (iCrest == 0) return svFail;

    int iBottom(w.size() - 1);
    for (; iBottom >= 1; iBottom--) { // Find last bottom
        if (w[iBottom - 1] > w[iBottom]) {
            break;
        }
    }

    if (iCrest < iBottom) {
        for (int i(w.size() - 1); i >= 0; i--) {
            if (w[i] > w[iCrest - 1]) {
                swap(w[i], w[iCrest - 1]);
                sort(w.begin() + iCrest, w.end());
                return w;
            }
        }
    } else {
        swap(w[iCrest - 1], w[iCrest]);
        return w;
    }

    return w;
}

int main()
{
    // freopen("output.txt", "w", stdout);
    string T_temp;
    getline(cin, T_temp);

    int T = stoi(ltrim(rtrim(T_temp)));

    for (int T_itr = 0; T_itr < T; T_itr++) {
        string w;
        getline(cin, w);

        string result = biggerIsGreater(w);

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
