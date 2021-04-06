#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

#ifndef MYUINT
    #define MYUINT
    #include "MyUint.h"
#endif

#ifndef MYUINT_CPP
    #define MYUINT_CPP
    #include "MyUint.cpp"
#endif

using namespace std;

int main(){

    MyUint A; cin >> A;
    MyUint B = Integer("123456789");
    MyUint C = Integer(123456789ll);

    int input; input = 123456789;

    if(B <= A) cout << A - B;
    else{
        cout << "-" << endl;
        cout << B - A << endl;
    }

    cout << "Adding A and B: " << A + B << endl; Print(A + input);
    cout << "Multiplying A and B: " << A * B << endl; Print(A * input);
    cout << "Dividing A and B: " << A / B << endl; Print(A / input);
    cout << "Modulating A and B: " << A % B << endl; Print(A % input);

    return 0;
}

