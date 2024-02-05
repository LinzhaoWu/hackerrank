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

class A
{
    public:
        A(){
            callA = 0;
        }
    private:
        int callA;
        void inc(){
            callA++;
        }

    protected:
        void func(int & a)
        {
            a = a * 2;
            inc();
        }
    public:
        int getA(){
            return callA;
        }
};

class B
{
    public:
        B(){
            callB = 0;
        }
    private:
        int callB;
        void inc(){
            callB++;
        }
    protected:
        void func(int & a)
        {
            a = a * 3;
            inc();
        }
    public:
        int getB(){
            return callB;
        }
};

class C
{
    public:
        C(){
            callC = 0;
        }
    private:
        int callC;
        void inc(){
            callC++;
        }
    protected:
        void func(int & a)
        {
            a = a * 5;
            inc();
        }
    public:
        int getC(){
            return callC;
        }
};

class D : public A, B, C
{

	int val;
	public:
		//Initially val is 1
		 D()
		 {
		 	val = 1;
		 }


		 //Implement this function
		 void update_val(int new_val)
		 {
            size_t cntA(0), cntB(0), cntC(0);
            while (new_val != 0 && new_val % 2 == 0) {
                A::func(val);
                cntA++;
                new_val /= 2;
            }
            while (new_val != 0 && new_val % 3 == 0) {
                B::func(val);
                cntB++;
                new_val /= 3;
            }
            while (new_val != 0 && new_val % 5 == 0) {
                C::func(val);
                cntC++;
                new_val /= 5;
            }

            std::cout << "A's func called " << cntA << " times" << std::endl;
            std::cout << "B's func called " << cntB << " times" << std::endl;
            std::cout << "C's func called " << cntC << " times" << std::endl;
		 }
		 //For Checking Purpose
		 void check(int); //Do not delete this line.
};

int main()
{
    uint32_t new_val;
    std::cin >> new_val;
    std::cout << "Value = " << new_val << std::endl;
    D d;
    d.update_val(new_val);
}