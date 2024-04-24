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
vector<string> split(const string &);

/*
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int queensAttack(int n, int k, int r_q, int c_q, vector<vector<int>> obstacles) {
    auto GetDistance = [r_q, c_q](int r, int c) -> int {
        if (c_q == c) return abs(r_q - r);
        else if (r_q == r) return abs(c_q - c);
        else return min(abs(r_q - r), abs(c_q - c));
    };

    const int MAXN = GetDistance(1, c_q);
    const int MAXS = GetDistance(n, c_q);
    const int MAXE = GetDistance(r_q, n);
    const int MAXW = GetDistance(r_q, 1);
    const int MAXNW = min(MAXN, MAXW);
    const int MAXSW = min(MAXS, MAXW);
    const int MAXNE = min(MAXN, MAXE);
    const int MAXSE = min(MAXS, MAXE);

    int ret(0);
    int minN = MAXN;
    int minS = MAXS;
    int minE = MAXE;
    int minW = MAXW;
    int minNE = MAXNE;
    int minNW = MAXNW;
    int minSE = MAXSE;
    int minSW = MAXSW;

    for (const auto& ob : obstacles) {
        const int dis = GetDistance(ob[0], ob[1]) - 1;
        if (ob[0] == r_q) {
            if (ob[1] > c_q) {
                minE = min(minE, dis);
            } else {
                minW = min(minW, dis);
            }
        } else if (ob[1] == c_q) {
            if (ob[0] > r_q) {
                minS = min(minS, dis);
            } else {
                minN = min(minN, dis);
            }
        } else if (abs(r_q - ob[0]) == abs(c_q - ob[1])) {
            if (r_q - ob[0] > 0 && c_q - ob[1] > 0) { 
                minNW = min(minNW, dis);
            } else if (r_q - ob[0] > 0 && c_q - ob[1] < 0) {
                minNE = min(minNE, dis);
            } else if (r_q - ob[0] < 0 && c_q - ob[1] < 0) {
                minSE = min(minSE, dis);
            } else if (r_q - ob[0] < 0 && c_q - ob[1] > 0) {
                minSW = min(minSW, dis);
            } 
        }
    }
    return minN + minS + minE + minW + minNE + minNW + minSE + minSW;
}

int main()
{
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int k = stoi(first_multiple_input[1]);

    string second_multiple_input_temp;
    getline(cin, second_multiple_input_temp);

    vector<string> second_multiple_input = split(rtrim(second_multiple_input_temp));

    int r_q = stoi(second_multiple_input[0]);

    int c_q = stoi(second_multiple_input[1]);

    vector<vector<int>> obstacles(k);

    for (int i = 0; i < k; i++) {
        obstacles[i].resize(2);

        string obstacles_row_temp_temp;
        getline(cin, obstacles_row_temp_temp);

        vector<string> obstacles_row_temp = split(rtrim(obstacles_row_temp_temp));

        for (int j = 0; j < 2; j++) {
            int obstacles_row_item = stoi(obstacles_row_temp[j]);

            obstacles[i][j] = obstacles_row_item;
        }
    }

    int result = queensAttack(n, k, r_q, c_q, obstacles);

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
