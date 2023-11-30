#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
#include <vector>
using namespace std;


std::vector<int> stringToVector(const LongInt& inputNum) {
    std::vector<int> result;
    for (auto it = inputNum.rbegin(); it != inputNum.rend(); ++it) {
        result.push_back(*it - '0'); 
    }
    
    return result;
}
int main() {
    LongInt a, b, c;
    cin >> a;
    cin >> b;

    cout << "karatsuba = " << LongInt::karatsuba_multiply(a, b) << endl;
    cout << "toom_cook = " << LongInt::toom_cook_multiply(a, b) << endl;
    cout << "modular m = " << LongInt::shenhageMultiply(a, b) << endl;// таке собі...
    
    std::vector<int> coeffsA = stringToVector(a);
    std::vector<int> coeffsB = stringToVector(b); 

    LongInt numA(coeffsA);
    LongInt numB(coeffsB);

    LongInt result = LongInt::schonhageStrassenMultiply(numA, numB);
    for (int i = result.coefficients.size() - 1; i >= 0; --i) {
        std::cout << result.coefficients[i];
    }
}