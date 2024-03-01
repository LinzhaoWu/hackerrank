#include <stdio.h>
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


using namespace std;

/*
 * Complete the 'timeConversion' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

string timeConversion(string s) {
    int iHour(0);
    char sMS[6] = {0};
    char cAP(0);
    sscanf(s.c_str(), "%2d:%5c%cM", &iHour, sMS, &cAP);

    if (cAP == 'A') {
        if (iHour == 12) iHour = 0;
    } else if (cAP == 'P') {
        if (iHour != 12) iHour += 12;
    }
    char sRet[20];
    if (iHour < 10) sprintf(sRet, "0%1d:%s", iHour, sMS);
    else sprintf(sRet, "%2d:%s", iHour, sMS);
    return string(sRet);
}

int main()
{
    // ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = timeConversion(s);

    std::cout << result << "\n";

    // fout.close();

    return 0;
}
