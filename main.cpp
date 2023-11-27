#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
    LongInt a, b, c;
    cin >> a;
    cin >> b;

    cout << "karatsuba = " << LongInt::karatsuba_multiply(a, b) << endl;
    cout << "toom_cook = " << LongInt::toom_cook_multiply(a, b) << endl;
    cout << "modular m = " << LongInt::shenhageMultiply(a, b) << endl;// таке собі...
}