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
 * Complete the 'extraLongFactorials' function below.
 *
 * The function accepts INTEGER n as parameter.
 */

void extraLongFactorials(int n) {
    vector<int> arr ;
    arr.push_back(1) ;      //start with adding 1  to the vector arr
    
    //calculation
    for(int i=2; i<=n ; i++){
        int carry = 0 ;
        int size = arr.size() ;
        
        for(int j=0; j<size ;j++){
            
            int value = arr[j]*i + carry ;
            arr[j] = value%10 ;
            carry = value/10 ;
        }
        while (carry) {
            arr.push_back(carry%10) ;
            carry /= 10 ;
        }
    }
    
    //print the vector containing fact
    for(int i=arr.size()-1 ;i>=0; i--){
        cout<<arr[i] ;
    }
}

int main()
{
    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    extraLongFactorials(n);

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
