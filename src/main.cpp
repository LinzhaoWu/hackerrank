#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <deque>
#include <cstring>
#include <string>

#if 0
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
#else
int main() {
    std::string sLine;
    std::getline(std::cin, sLine);

    uint32_t nTestCases;
    if (1 != sscanf_s(sLine.c_str(), "%d", &nTestCases)) {
        return -1;
    }

    for (uint32_t i(0); i < nTestCases; i++) {
        std::getline(std::cin, sLine);
        uint32_t nElements, nSubStrings;
        if (2 != sscanf_s(sLine.c_str(), "%d %d", &nElements, &nSubStrings)) {
            return -1;
        }

        std::set<uint32_t> setSubArr;
        std::deque<uint32_t> dqSubArr;

        std::getline(std::cin, sLine);
        
        // For each line, get elements
        const auto svDelimiter = " ";
        for (auto token = std::strtok(sLine.data(), svDelimiter);
             token;
             token = std::strtok(nullptr, svDelimiter)) {

            const uint32_t uElement = std::stoi(std::string(token));
            setSubArr.insert(uElement);
            dqSubArr.push_back(uElement);

            if (dqSubArr.size() == nSubStrings) {
                std::cout << *setSubArr.crbegin() << " ";
                setSubArr.erase(dqSubArr.front());
                dqSubArr.pop_front();
            } 
        }
        std::cout << std::endl;
    }

    return 0;
}
#endif