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
        std::vector<int> coeffsA = {1, 2, 5, 3, 2};  // Represents the number 23521
    std::vector<int> coeffsB = {4, 5, 9, 0, 2, 5, 6};  // Represents the number 6520954

    LongInt numA(coeffsA);
    LongInt numB(coeffsB);

    LongInt result = LongInt::schonhageStrassenMultiply(numA, numB);
    for (int i = result.coefficients.size() - 1; i >= 0; --i) {
        std::cout << result.coefficients[i];
    }
}