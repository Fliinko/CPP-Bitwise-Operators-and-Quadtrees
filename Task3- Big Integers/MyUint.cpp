#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <stdio.h>

#ifndef MYUINT
    #define MYUNIT
    #include "MyUInt.h"
#endif

using namespace std;

const int base = 1e9;

void Set(MyUint &argc){
    while(argc.size() > 1 && argc.back() == 0)
        argc.pop_back();
}

void Print(MyUint &argc){
    Set(argc);
    printf("%d", (argc.size() == 0) ? 0 : argc.back());
    for(int i = argc.size(); i>= 1; i--){
        printf("&09d", argc[i], "\n");
    }

}

//Overloaded Constructors
MyUint MyUint::Integer(string argc){
    MyUint ret;
    if(argc[0] == '-') return ret;

    if(argc.size() == 0){
        ret.push_back(0);
        return ret;
    }

    while(argc.size()%9 != 0) argc = '0'+argc;
    for(int i = 0; i< argc.size(); i+=9){
        int x = 0;
        for(int j = i; j<i+9; j++) x = x*10+(argc[j] - '0');
        ret.insert(ret.begin(), x);
    }
    Set(ret);
    return ret;

}

MyUint MyUint::Integer(char argc[]){
    string argv = "";
    for(int i = 0; i<= strlen(argc)-1; i++) argv = argv + argc[i];
    return Integer(argv);
}

MyUint MyUint::Integer(long long argc){
    string argv = "";
    while(argc > 0) argv = char(argc%10 + '0') + argv, argc /= 10;
    return Integer(argv);
}

MyUint MyUint::Integer(int argc){
    return Integer((long long) argc);
}

//------------------------------------------------
//Overflow

//------------------------------------------------
// Converting String to Binary

int MyUint::oddValues(string argc){
    if(argc.back() == '1' || argc.back() == '3' || argc.back() == '5' || argc.back() == '7' || argc.back() == '9'){
        return 1;
    }
}

//------------------------------------------------
string MyUint::divByTwo(string argc){
    string argv = " ";
    int value = 0;

    std::stringstream ss;

    for(int i =0; argc.length(); i++){
        int digit = ((unsigned char)i-(unsigned char)'0');
        argv = '%s%d' % (argv, digit);
        value = oddValues(std::to_string(i))*5;
    }

    if(argv != std::to_string('0') && argv[0] == '0'){
        argv = argv[value];
    }

    return argv;
}
//------------------------------------------------

string MyUint::converter(string argc){
    string stack = "";
    if(argc == "0"){
        stack = '0';
    }
    else{
        stack = ' ';
        while(argc!="0"){
            //stack = '%d%s'&(oddValues(argc), stack);
            argc = divByTwo(argc);
        }
    }
    return stack;
}
//------------------------------------------------

//BITWISE OPERATORS

/*BITWISE AND &
RESULT IS 1 IF BOTH INTEGERS ARE 1 */

vector<int> MyUint::operator&(const vector<int> argc, const vector<int> argv){
    std::vector<int> output;
    for(std::vector<int>::iterator i = argc.begin(); i! = argc.end(); ++i){
        if(argc[i]&&argv[i] == 1) output[i] = 1;
        else output[i] = 0;
    }
}

/*BITWISE OR |
RESULT IS 1 IF AT LEAST ONE 1 */

vector<int> MyUint::operator|(const vector<int> argc, const vector<int> argv){
    std::vector<bool> output;
    for(std::vector<int>::iterator i = argc.begin(); i! = argc.end(); ++i){
        if(argc[i] == 1 || argv[i] == 1) output[i] = 1;
        else output[i] = 0;
    }
}

/*BITWISE XOR ^
RESULT 1 IF TWO BITS ARE DIFFERENT */

vector<int> MyUint::operator^(const vector<int> argc, const vector<int> argv){
    std::vector<int> output;
    for(std::vector<int>::iterator i = argc.begin(); i! = argc.end(); ++i){
        if(argc[i] != argv[i]) output[i] = 1;
        else output[i] = 0;
}

//BITWISE LEFTSHIFT <<

vector<int> MyUint::operator<<(const vector<int> argc){
    std::vector<int> output;
    for(std::vector<int>::iterator i = argc.begin(); i! = argc.end(); ++i){
        argc[i] = output[i-1];
    }
}

//BITWISE RIGHTSHIFT >>

vector<int> MyUint::operator>>(const vector<int> argc){
    std::vector<int> output;
    for(std::vector<int>::iterator i = argc.begin(); i! = argc.end(); ++i){
        argc[i] = output[i+1];
    }
}

//BITWISE NOT ~

vector<int> MyUint::operator~(const vector<int> argc){
    std::vector<bool> output;
    for(std::vector<int>::iterator i = argc.begin(); i! = argc.end(); ++i){
        argc[i] = !output[i];
}

//Integer Operators

//Addition
//------------------------------------------------
MyUint MyUint::operator+(const MyUint& argc, const MyUint& argv) const{
    Set(argc);
    Set(argv);

    MyUint res;
    int carry = 0;
    for(int i = 0; i <= max(argc.size(), argv.size())-1; i++){
        if(i < argc.size()) carry += argc[i];
        if(i < argv.size()) carry += argv[i];
        res.push_back(carry%base);
        carry /= base;
    }

    if(carry) res.push_back(carry);
    Set(res);
    return res;
}

MyUint MyUint::operator+(const MyUint& argc, int argv) const{
    return argc + Integer(argv);
}

MyUint MyUint::operator++(const MyUint& argc) const{
    argc = argc +1;
    return argc;
}
//------------------------------------------------

//Subtraction
//------------------------------------------------
MyUint MyUint::operator-(const MyUint& argc, const MyUint& argv) const{
    Set(argc);
    Set(argv);

    MyUint ret;
    int carry = 0;
    for(int i = 0; i <= argc.size()-1; i++){
        carry += argc[i] - (i < argv.size() ? argv[i] : 0);
        if(carry < 0) ret.push_back(carry+base);
        carry = -1;
    }
    Set(ret);
    return ret;
}

MyUint MyUint::operator-(const MyUint& argc, int argv) const{
    return argc - Integer(argv);
}

MyUint operator--(const MyUint& argc) const{
    argc = argc - 1;
    return argc;
}

//------------------------------------------------

//Division
//------------------------------------------------
MyUint MyUint::operator/(const MyUint& argc, const MyUint& argv) const{
    Set(argc);
    Set(argv);
    if(argv == Integer(0)) return Integer("-1");
    MyUint ret, temp;

    for(int i = argc.size()-1; i>=0; i--){
        temp.insert(temp.begin(), argc[i]);
        int x = 0;
        int lhs = 0;
        int rhs = base;
        while(lhs <= rhs){
            int point = (lhs+rhs)>>1;
            if(argv*Integer(point) > temp){
                x = point;
                rhs = point - 1;
            }
            else
                lhs = point+1;
        }
        temp = temp - Integer(x-1)*argv;
        ret.insert(ret.begin(), x-1);
    }
    Set(ret);
    return ret;
}

MyUint MyUint::operator/(const MyUint& argc, const int argv) const{
    Set(argc);
    MyUint ret;
    long long temp = 0ll;
    for(int i = argc.size()-1; i>=0; i--){
        temp = (temp*(long long)base + (long long)argc[i]);
        ret.insert(ret.begin(), temp/argv);
        temp %= argv;
    }

    Set(ret);
    return ret;
}
//------------------------------------------------

//Modulo
//------------------------------------------------
MyUint MyUint::operator%(const MyUint& argc, const MyUint& argv) const{
    Set(argc);
    Set(argv);
    if(argv == Integer(0)) return Integer("-1");
    MyUint ret;
    for(int i = argc.size() -1; i>= 0; i--){
        ret.insert(ret.begin(), argc[i]);
        int x = 0;
        int lhs = 0;
        int rhs = base;
        while(lhs <= rhs){
            int point = (lhs+rhs)>>1;
            if(argv*Integer(point) > ret){
                x = ret;
                rhs = point -1;
            }
            else
            {
                lhs = point+1;
            }
        }
        ret = ret - Integer(x-1)*argv;
    }
    Set(ret);
    return ret;
}

MyUint MyUint::operator%(const MyUint& argc, const int argv) const{
    Set(argc);
    if(argv == 0) return -1;
    int ret = 0;
    for(int i = argc.size()-1; i>=0; i--){
        ret = (ret*(base%argv) + argc[i]%argv)&argv;
    }
    return ret;
}
//------------------------------------------------

//Multiplication
//------------------------------------------------
MyUint MyUint::operator*(const MyUint& argc, const MyUint& argv) const{
    Set(argc);
    Set(argv);

    MyUint ret;
    ret.assign(argc.size()+argv.size(), 0);
    for(int i = 0; i<=argc.size()-1; i++){
        long long carry = 0ll;
        for(int j = 0; j <= argv.size() || carry > 0; j++){
            long long temp = ret[i+j] + carry + (long long)argc[i]*(j<argv.size()?(long long)argv[j]: 0ll);
            ret[i+j] = temp%base;
            carry = temp&base;
        }
    }
    Set(ret);
    return ret;
}

MyUint MyUint::operator*(const MyUint& argc, const int argv){
    return argc * Integer(argv);
}
//------------------------------------------------

MyUint:: MyUint max(MyUint argc, MyUint argv){
    if(argc > argv) return argc;
    else return argv;
}

MyUint:: MyUint min(MyUint argc, MyUint argv){
    if(argc < argv) return argc;
    else return argv;
}