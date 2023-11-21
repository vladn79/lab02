#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
LongInt num1("123456789");
LongInt num2("987654321");

LongInt result1;
LongInt result2;
cout << num1 * num2 << endl;
cout << "Result: " << result1.karatsuba_multiply(num1, num2) << endl;
cout << "Result: " << result2.toom_cook_multiply(num1, num2)<< endl;


}