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

#include <deque>

class Person
{
public:
    Person(std::string nameFirst, std::string nameLast);

    friend std::ostream& operator<<(std::ostream &os, Person &p);

private:
    std::string mFirstName;
    std::string mLastName;
};

Person::Person(std::string nameFirst, std::string nameLast)
: mFirstName(nameFirst)
, mLastName(nameLast)
{
}

std::ostream& operator<<(std::ostream &os, Person& p)
{
    os << "first_name=" << p.mFirstName << ",last_name=" << p.mLastName;
    return os;
}

int main()
{
    std::string sFirstName, sSecondName, event;
    std::cin >> sFirstName >> sSecondName >> event;

    Person p(sFirstName, sSecondName);

    std::cout << p << " " << event << std::endl;
}
