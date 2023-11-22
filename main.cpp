#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
    LongInt a("12");
    LongInt b("10");
    
    
    LongInt c = a.karatsuba_multiply(a, b);
    cout << c.value<< endl;
    return 0;
}
