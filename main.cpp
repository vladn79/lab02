#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
    LongInt a, b;
    cin >> a;
    cin >> b;
    int c = 6;
    cout << "multtttt = " << (a * b).value<< endl;//correct
    cout << "mul11111 = " << (a * c).value<< endl;//correct
    cout << "division = " << (a / c).value<< endl;//correct
    cout << "division11 = " << (a % c).value<< endl;
    cout <<"karatsuba = " << LongInt::karatsuba_multiply(a, b) << endl;
    cout <<"toom_cook = " << LongInt::toom_cook_multiply(a, b) << endl;
}