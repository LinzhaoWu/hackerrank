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
int a[10010];
deque<int> q;
void add(int x) {
    while (!q.empty() && q.back() < x)
        q.pop_back();
    q.push_back(x);
}
void remove(int x) {
    if (!q.empty() && q.front() == x) {
        q.pop_front();
    }
}
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        q.clear();
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < k; ++i) {
            add(a[i]);
        }
        for (int i = k; i <= n; ++i) {
            cout << q.front() << ' ';
            remove(a[i - k]);
            add(a[i]);
        }
        cout << endl;
        /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    }
    return 0;
}