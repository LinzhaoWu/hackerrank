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

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'breakingRecords' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY scores as parameter.
 */

vector<int> breakingRecords(vector<int> scores) {
    int iMax(scores.front());
    int iMin(scores.front());
    int iBest(0);
    int iWorst(0);
    for_each(scores.cbegin(), scores.cend(), 
        [&](const auto& e) {
            if (e > iMax) {
                iBest++;
                iMax = e;
            } else if (e < iMin) {
                iWorst++;
                iMin = e;
            }
        }
    );
    return vector{iBest, iWorst};
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(n_temp);

    string scores_temp_temp;
    getline(cin, scores_temp_temp);

    vector<string> scores_temp = split((scores_temp_temp));

    vector<int> scores(n);

    for (int i = 0; i < n; i++) {
        int scores_item = stoi(scores_temp[i]);

        scores[i] = scores_item;
    }

    vector<int> result = breakingRecords(scores);

    for (size_t i = 0; i < result.size(); i++) {
        cout << result[i];

        if (i != result.size() - 1) {
            cout << " ";
        }
    }

    cout << "\n";

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), isspace)
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), isspace).base(),
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
