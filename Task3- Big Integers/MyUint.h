#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

template<typename Object>
class MyUint{
    private:
        const int base;

    public:
        
        void Set(MyUint& argc);
        void Print(MyUint& argc);

        MyUint Integer(string argc);
        MyUint Integer(char argc[]);
        MyUint Integer(long long argc);
        MyUint Integer(int argc);

        int oddValues(string argc);
        string divByTwo(string argc);
        string converter(string argc);

        vector<int> operator&(const vector<int> argc, const vector<int> argv);
        vector<int> operator|(const vector<int> argc, const vector<int> argv);
        vector<int> operator^(const vector<int> argc, const vector<int> argv);
        vector<int> operator<<(const vector<int> argc);
        vector<int> operator>>(const vector<int> argc);
        vector<int> operator~(const vector<int> argc);

        MyUint operator+(const MyUint& argc, const MyUint& argv) const;
        MyUint operator+(const MyUint& argc, int argv) const;
        MyUint operator++(const MyUint& argc) const;

        MyUint operator-(const MyUint& argc, const MyUint& argv) const;
        MyUint operator-(const MyUint& argc, int argv) const;
        MyUint operator--(const MyUint& argc) const;

        MyUint operator/(const MyUint& argc, const MyUint& argv) const;
        MyUint operator/(const MyUint& argc, const int argv) const;

        MyUint operator%(const MyUint& argc, const MyUint& argv) const;
        MyUint operator%(const MyUint& argc, const int argv) const;

        MyUint operator*(const MyUint& argc, const MyUint& argv) const;
        MyUint operator*(const MyUint& argc, const int argv);

        MyUint max(MyUint argc, MyUint argv);
        MyUint min(MyUint argc, MyUint argv);


};