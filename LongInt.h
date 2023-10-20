#include <iostream>
#include <vector>
#include <string>

class LongInt {
private:
    std::vector<int> digits;

public:
    LongInt(std::string n_str) {
        for (char digit : n_str) {
            digits.push_back(digit - '0');
        }
    }

    void printNumber() const {
        for (int digit : digits) {
            std::cout << digit;
        }
        std::cout << std::endl;
    }
};



