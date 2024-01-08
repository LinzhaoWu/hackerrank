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

int32_t largest_proper_divisor(int32_t n)
{
    std::string expt = "largest proper divisor is not defined for n=" + std::to_string(n);
    if (n < 2) throw std::invalid_argument(expt);

    for (int32_t i(n / 2); i >= 1; i--) {
        if (0 == n % i) return i;
    }

    return n;
}

int main()
{
    int32_t n;

    std::cin >> n;

    try {
        int32_t ret = largest_proper_divisor(n);
        std::cout << "result=" << ret << std::endl;

    } catch (std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << "returning control flow to caller" << std::endl;

    return 0;
}