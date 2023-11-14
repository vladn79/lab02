#include <iostream>
#include "LongInt.h"
//#include "Karatsuba.h"
int main() {
      std::string num1 = "11";
      std::string num2 = "3";

      LongInt longNum1(num1);
      LongInt longNum2(num2);

      LongInt sum = longNum1 + longNum2;
      LongInt diff = longNum1 - longNum2;
      LongInt pr = longNum1 * longNum2;


      std::cout << "Sum: " << sum << std::endl;
      std::cout << "Diff: " << diff << std::endl;
      std::cout << "prod: " << pr << std::endl;


    return 0;
}