#include <iostream>
#include "LongInt.h"
#include "LongInt.cpp"
using namespace std;

int main() {
LongInt num1("123456789");
LongInt num2("987654321");

LongInt result;
std::cout << "Result: " << result.karatsuba_multiply(num1, num2) << std::endl;

}