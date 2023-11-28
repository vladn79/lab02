#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
#include <vector>
using namespace std;

int main() {
    LongInt a, b, c;
    cin >> a;
    cin >> b;

    cout << "karatsuba = " << LongInt::karatsuba_multiply(a, b) << endl;
    cout << "toom_cook = " << LongInt::toom_cook_multiply(a, b) << endl;
    cout << "modular m = " << LongInt::shenhageMultiply(a, b) << endl;// таке собі...
    std::vector<int> coeffsA = {3, 2};
    std::vector<int> coeffsB = {5}; 

    LongInt numA(coeffsA);
    LongInt numB(coeffsB);

    LongInt result = LongInt::schonhageStrassenMultiply(numA, numB);
    for (int i = result.coefficients.size() - 1; i >= 0; --i) {
        std::cout << result.coefficients[i];
    }
}