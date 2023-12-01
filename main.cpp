#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
#include <vector>

using namespace std;


vector<int> stringToVector(const LongInt& inputNum) {
    vector<int> result;
    for (auto it = inputNum.rbegin(); it != inputNum.rend(); ++it) {
        result.push_back(*it - '0'); 
    }
    
    return result;
}
int main() {
    LongInt a, b;
    cin >> a;
    cin >> b;

    cout << "karatsuba = " << LongInt::karatsuba_multiply(a, b) << endl;
    cout << "Toom_Cook = " << LongInt::toom_cook_multiply(a, b) << endl;
    cout << "modular m = " << LongInt::shenhageMultiply(a, b) << endl;
    
    vector<int> coeffsA = stringToVector(a);
    vector<int> coeffsB = stringToVector(b); 

    LongInt numA(coeffsA);
    LongInt numB(coeffsB);
    cout << "Schonhage = ";
    LongInt result = LongInt::schonhageStrassenMultiply(numA, numB);
    result.removeLeadingZero();
    for (int i = result.coefficients.size() - 1; i >= 0; --i) {
        std::cout << result.coefficients[i];
    }
    cout << endl;

    
    cout << "Ferma : " << a.isPrimeFermat(a, 5) << endl;
    cout << "MillerRabin : " << a.millerRabinTest(a, 5) << endl;
    cout<< "Solovey S : " << a.Solovey_Str(a, 5);
}