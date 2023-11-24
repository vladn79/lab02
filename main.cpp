#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
    LongInt n, m;
    cin >> n;
    cin >> m;
    cout << n.ferma() << endl;

    
    cout << n.karatsuba_multiply(n, m) << endl;
    cout << n.toom_cook_multiply(n, m) << endl; 
    return 0;

}