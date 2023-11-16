#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
    LongInt x, y;
    cin >> x;
    cin >> y;
    LongInt z;
    cout << z.karatsubaMultiply(x, y);  

    return 0;
}