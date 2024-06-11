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

/*
 * Complete the 'commonChild' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING s1
 *  2. STRING s2
 */
// #define OTHERS
int commonChild(string s1, string s2) {
#ifdef OTHERS
    int m = s1.length();
    int n = s2.length();
    
    vector<int> curr(n+1,0), prev(n+1,0);
    
    for(int i=1;i<=m;++i)
    {
        cout<< s1[i-1] << "\r\n";
        for(int j=1;j<=n;++j)
        {
            auto& a = s1[i-1];
            auto& b = s2[j-1];
            if(a == b)
                curr[j] = 1 + prev[j-1];
            else
                curr[j] = max(curr[j-1],prev[j]);
        }
        cout<< "curr " << curr[0] << " " << curr[1]<< " " << curr[2]<< " " << curr[3]<< " " << curr[4]<< " " << curr[5]<< " " << curr[6]<< "\r\n";
        cout<< "prev " << prev[0] << " " << prev[1]<< " " << prev[2]<< " " << prev[3]<< " " << prev[4]<< " " << prev[5]<< " " << prev[6]<< "\r\n";
        prev = curr;
    }
    return curr[n];
#else
    vector dp(s2.size() + 1, vector<size_t>(s1.size() + 1, 0));

    for (size_t j(1); j <= s2.size(); j++) {
        for (size_t i(1); i <= s1.size(); i++) {
            auto& a = s1[i - 1];
            auto& b = s2[j - 1];
            if (a == b) dp[j][i] = dp[j - 1][i - 1] + 1;
            else dp[j][i] = max(dp[j -1][i], dp[j][i - 1]);
        }
    }
    return dp[s2.size()][s1.size()];
#endif
}

int main()
{
    string s1;
    getline(cin, s1);

    string s2;
    getline(cin, s2);

    int result = commonChild(s1, s2);

    cout << result << "\n";

    return 0;
}
