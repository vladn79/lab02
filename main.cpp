#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
    LongInt x, y;
    cin >> x;
    cin >> y;
    cout <<"x = "<< x << endl;
    cout <<"y = "<< y << endl;
    cout <<"x + y = "<< x + y;
    cout <<"x - y = "<< x - y;
    bool ex = (x + y) != x;
    cout << ex;

    return 0;
}