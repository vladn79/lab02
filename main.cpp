#include <iostream>
#include "LongInt.h"
int main() {
    std::string num1 = "1111111111111111111111111111111111111111";
    std::string num2 = "3333333333333333333333333333333333333333";

    LongInt longNum1(num1);
    LongInt longNum2(num2);

    LongInt sum = longNum1 + longNum2;
    LongInt diff = longNum2 - longNum1;

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Diff: " << diff << std::endl;


    return 0;
}