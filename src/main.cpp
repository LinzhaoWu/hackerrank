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

#include <chrono>
using namespace std::chrono;

#if 0 // Too Slow
int main() {
    uint32_t nTestCases;
    std::cin >> nTestCases;

    for (uint32_t i(0); i < nTestCases; i++) {
        uint32_t nElements, nSubStrings;
        std::cin >> nElements >> nSubStrings;

        std::set<uint32_t> setSubArr;
        std::deque<uint32_t> dqSubArr;

        // // For each line, get elements
        for (uint32_t i(0); i < nElements; i++) {
            uint32_t uElement;
            std::cin >> uElement;
            setSubArr.insert(uElement);
            dqSubArr.push_back(uElement);

            if (dqSubArr.size() == nSubStrings) {
                std::cout << *setSubArr.rbegin() << " ";
                setSubArr.erase(dqSubArr.front());
                dqSubArr.pop_front();
            } 
        }
        std::cout << std::endl;
    }

    return 0;
}
#endif

#define TEST

// #define TIME_MEASUREMENT
#ifdef TIME_MEASUREMENT
auto start = high_resolution_clock::now();
auto stop = high_resolution_clock::now();
auto a = stop - stop;
auto b = stop - stop;
auto c = stop - stop;
#endif

// strtok() seems to be slower than find_first_of()...
// The measurement result is:
// * For the strtok() version:
//          A:322 B:3268785 C:573250
// * For the find_first_of() version:
//          A:149 B:2952008 C:81
//
// Conclusion:
// It is less likely due to the function of strtok() and find_first_of().
// More likely, it is because strtok() can only use std::string and it need to change memory to add '\0', 
// but find_first_of() can use std::string_view() and not changing memory, thus faster.


#if 0 
int main() {
    std::string sLine;
    #ifdef TEST
    std::ifstream infile("src/dequeSTL_testcase.txt");

    std::getline(infile, sLine);
    #else
    std::getline(std::cin, sLine);
    #endif

    uint32_t nTestCases;
    if (1 != sscanf(sLine.c_str(), "%d", &nTestCases)) {
        return -1;
    }


    for (uint32_t i(0); i < nTestCases; i++) {
        #ifdef TEST
        std::getline(infile, sLine);
        #else
        std::getline(std::cin, sLine);
        #endif
        uint32_t nElements, nSubStrings;
        if (2 != sscanf(sLine.c_str(), "%d %d", &nElements, &nSubStrings)) {
            return -1;
        }

        std::multiset<uint32_t> setSubArr;
        std::deque<uint32_t> dqSubArr;

        #ifdef TEST
        std::getline(infile, sLine);
        #else
        std::getline(std::cin, sLine);
        #endif
        
        // For each line, get elements
        const auto svDelimiter = " ";
        #ifdef TIME_MEASUREMENT
        start = high_resolution_clock::now();
        #endif
        auto token = std::strtok(sLine.data(), svDelimiter);
        #ifdef TIME_MEASUREMENT
        stop = high_resolution_clock::now();
        a += stop - start;
        #endif

        while (token) {
            #ifdef TIME_MEASUREMENT
            start = high_resolution_clock::now();
            #endif
            const uint32_t uElement = std::stoi(std::string(token));
            #ifdef TIME_MEASUREMENT
            stop = high_resolution_clock::now();
            b += stop - start;
            #endif

            setSubArr.insert(uElement);
            dqSubArr.push_back(uElement);

            if (dqSubArr.size() == nSubStrings) {
                std::cout << *setSubArr.crbegin() << " ";

                setSubArr.erase(setSubArr.lower_bound(dqSubArr.front()));
                dqSubArr.pop_front();
            } 

            #ifdef TIME_MEASUREMENT
            start = high_resolution_clock::now();
            #endif

            token = std::strtok(nullptr, svDelimiter);

            #ifdef TIME_MEASUREMENT
            stop = high_resolution_clock::now();
            c += stop - start;
            #endif
        }
        std::cout << std::endl;
    }

    #ifdef TIME_MEASUREMENT
    std::cout << "A:" << duration_cast<microseconds>(a).count() << std::endl;
    std::cout << "B:" << duration_cast<microseconds>(b).count() << std::endl;
    std::cout << "C:" << duration_cast<microseconds>(c).count() << std::endl;
    #endif

    return 0;
}

#else
static std::multiset<uint32_t> setSubArr;
static std::deque<uint32_t> dqSubArr;

void ProcessElement(const uint32_t uElement, const uint32_t nSubStrings)
{
    setSubArr.insert(uElement);
    dqSubArr.push_back(uElement);

    if (dqSubArr.size() == nSubStrings) {
        std::cout << *setSubArr.crbegin() << " ";

        setSubArr.erase(setSubArr.lower_bound(dqSubArr.front()));
        dqSubArr.pop_front();
    } 
}

int main() {
    std::string sLine;
    #ifdef TEST
    std::ifstream infile("src/dequeSTL_testcase.txt");

    std::getline(infile, sLine);
    #else
    std::getline(std::cin, sLine);
    #endif

    uint32_t nTestCases;
    if (1 != sscanf_s(sLine.c_str(), "%d", &nTestCases)) {
        return -1;
    }

    for (uint32_t i(0); i < nTestCases; i++) {
        #ifdef TEST
        std::getline(infile, sLine);
        #else
        std::getline(std::cin, sLine);
        #endif

        uint32_t nElements, nSubStrings;
        if (2 != sscanf_s(sLine.c_str(), "%d %d", &nElements, &nSubStrings)) {
            return -1;
        }


        #ifdef TEST
        std::getline(infile, sLine);
        #else
        std::getline(std::cin, sLine);
        #endif
        
        // For each line, get elements
        const auto svDelimiter = ' ';
        std::string_view svLine = sLine;

        std::size_t posStart = 0;
        while (svLine.at(posStart) == svDelimiter) posStart++;

        #ifdef TIME_MEASUREMENT
        start = high_resolution_clock::now();
        #endif

        std::size_t posEnd = svLine.find(svDelimiter, posStart);

        #ifdef TIME_MEASUREMENT
        stop = high_resolution_clock::now();
        a += stop - start;
        #endif

        while (posEnd != std::string_view::npos) {

            #ifdef TIME_MEASUREMENT
            start = high_resolution_clock::now();
            #endif

            const auto svElement = svLine.substr(posStart, posEnd - posStart);
            const uint32_t uElement = std::stoi(std::string(svElement));

            #ifdef TIME_MEASUREMENT
            stop = high_resolution_clock::now();
            b += stop - start;
            #endif

            ProcessElement(uElement, nSubStrings);

            posStart = posEnd + 1;
            posEnd = svLine.find_first_of(svDelimiter, posStart);
        }

        #ifdef TIME_MEASUREMENT
        start = high_resolution_clock::now();
        #endif

        const auto svElement = svLine.substr(posStart, svLine.size() - posStart);

        #ifdef TIME_MEASUREMENT
        stop = high_resolution_clock::now();
        c += stop - start;
        #endif

        if (!svElement.empty()) {
            const uint32_t uElement = std::stoi(std::string(svElement));
            ProcessElement(uElement, nSubStrings);
        }

        std::cout << std::endl;

        setSubArr.clear();
        dqSubArr.clear();
    }

    #ifdef TIME_MEASUREMENT
    std::cout << "A:" << duration_cast<microseconds>(a).count() << std::endl;
    std::cout << "B:" << duration_cast<microseconds>(b).count() << std::endl;
    std::cout << "C:" << duration_cast<microseconds>(c).count() << std::endl;
    #endif

    return 0;
}
#endif