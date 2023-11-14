#include <iostream>
#include <vector>
#include <algorithm>

class LongInt {
private:
    std::vector<int> digits;

public:
    LongInt() {}

    LongInt(const std::string& numStr) {
        for (char digit : numStr) {
            digits.push_back(digit - '0');
        }
        std::reverse(digits.begin(), digits.end());
    }

    LongInt operator+(const LongInt& other) const {
        LongInt result;
        int carry = 0;
        int maxSize = std::max(digits.size(), other.digits.size());

        for (int i = 0; i < maxSize; ++i) {
            int sum = carry;
            if (i < digits.size()) {
                sum += digits[i];
            }
            if (i < other.digits.size()) {
                sum += other.digits[i];
            }
            carry = sum / 10;
            result.digits.push_back(sum % 10);
        }

        if (carry > 0) {
            result.digits.push_back(carry);
        }

        return result;
    }

    LongInt operator-(const LongInt& other) const {
        LongInt result;
        int borrow = 0;
        int maxSize = std::max(digits.size(), other.digits.size());

        for (int i = 0; i < maxSize; ++i) {
            int diff = digits[i] - borrow;
            if (i < other.digits.size()) {
                diff -= other.digits[i];
            }
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits.push_back(diff);
        }

        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }

        return result;
    }
    LongInt operator*(const LongInt& other) const {
    LongInt result("0");

    for (int i = 0; i < digits.size(); ++i) {
        LongInt partialProduct;
        int carry = 0;

        for (int j = 0; j < other.digits.size(); ++j) {
            int product = digits[i] * other.digits[j] + carry;
            carry = product / 10;
            partialProduct.digits.push_back(product % 10);
        }

        while (carry > 0) {
            partialProduct.digits.push_back(carry % 10);
            carry /= 10;
        }
        
        for (int k = 0; k < i; ++k) {
            partialProduct.digits.insert(partialProduct.digits.begin(), 0);
        }

        result = result + partialProduct;
    }

    return result;
}


    friend std::ostream& operator<<(std::ostream& os, const LongInt& num) {
        for (auto it = num.digits.rbegin(); it != num.digits.rend(); it++) {
            os << *it;
        }
        return os;
    }
};



