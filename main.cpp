#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
#include <vector>
using namespace std;

int main() {
    LongInt a, b, c;
    int n = 5;

    cin >> c;


    cout << isPrimeFermat(c, n);
    return 0;

}