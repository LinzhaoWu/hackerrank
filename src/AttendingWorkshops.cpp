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
#include <memory>
#include <unordered_set>

#include <deque>

struct Workshop
{
    int m_start_time;
    int m_duration;
    int m_end_time;

    Workshop(int a_start_time, int a_duration);
};

Workshop::Workshop(int a_start_time, int a_duration)
: m_start_time(a_start_time)
, m_duration(a_duration)
, m_end_time(a_start_time + a_duration)
{
}

struct Available_Workshops
{
    int m_n;
    std::vector<Workshop> m_vect;
};

Available_Workshops* initialize (int start_time[], int duration[], int n)
{
    Available_Workshops* pAW = new Available_Workshops();
    for (int i(0); i < n; i++) {
        pAW->m_vect.emplace_back(start_time[i], duration[i]);
    }
    pAW->m_n = n;
    return pAW;
}

int CalculateMaxWorkshops(Available_Workshops* pAW)
{
    Available_Workshops& aw = *pAW;
    std::sort(aw.m_vect.begin(), aw.m_vect.end(), 
        [](const auto& first, const auto& second) -> bool{
            return first.m_end_time < second.m_end_time;
        }
    );

    int ret = 0;
    int cur_time = -1;
    for (uint32_t i(0); i < aw.m_vect.size(); i++) {
        if (aw.m_vect.at(i).m_start_time >= cur_time) {
            cur_time = aw.m_vect.at(i).m_end_time;
            ret++;
        }
    }
    return ret;
}

int main()
{
    size_t nWS(0);
    std::cin >> nWS;

    int* p_start_time = new int[nWS];
    int* p_duration_time = new int[nWS];

    for (int i(0); i < nWS; i++) {
        std::cin >> p_start_time[i];
    }
    for (int i(0); i < nWS; i++) {
        std::cin >> p_duration_time[i];
    }

    Available_Workshops* pAW = initialize(p_start_time, p_duration_time, nWS);

    std::cout << CalculateMaxWorkshops(pAW) << "\n";

    delete[] p_start_time;
    delete[] p_duration_time;

    delete pAW;
}