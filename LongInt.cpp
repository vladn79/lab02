#include "LongInt.h"
#include <algorithm>

LongInt::LongInt() {}

LongInt::LongInt(const std::string& numStr) {
    for (char digit : numStr) {
        digits.push_back(digit - '0');
    }
    std::reverse(digits.begin(), digits.end());
}



bool LongInt:: operator==(const LongInt& other) {
    return digits == other.digits;
    }

bool LongInt::operator!=(const LongInt& other){
    return !(operator==(other));
    }

bool LongInt::operator >(const LongInt& other) {
    bool res;
    if (digits.size()!=other.digits.size()){
        res = digits.size()>other.digits.size()?true:false;
    }
    for (int i=int(digits.size())-1;i>=0;--i){
        if (digits[i] > other.digits[i]){
            res = true; break;
        }
        res = false;
    }
    return res;
}

bool LongInt::operator<=(const LongInt& other) {
    return not(operator>(other));
    }

bool LongInt:: operator>=(const LongInt& other) {
    return (operator>(other) or operator==(other));
    }

bool LongInt:: operator<(const LongInt& other) {
    return not(operator>=(other));
    }


LongInt LongInt::operator+(const LongInt& other) {
    LongInt result;

    int carry = 0;
    size_t maxLength = std::max(digits.size(), other.digits.size());

    for (size_t i = 0; i < maxLength || carry; ++i) {
        int sum = carry + (i < digits.size() ? digits[i] : 0) + (i < other.digits.size() ? other.digits[i] : 0);
        carry = sum / 10;
        result.digits.push_back(sum % 10);
    }

    return result;
}

 LongInt LongInt::operator-(const LongInt& other) const {
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

LongInt LongInt::operator*(const LongInt& other) const {
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

std::ostream& operator<<(std::ostream& out, LongInt num) {
    for (int i = int(num.digits.size()) - 1; i >= 0; --i) {
        out << num.digits[i];
    }
    out << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, LongInt& num) {
    std::string input;
    in >> input;
    num = LongInt(input);
    return in;
}

LongInt LongInt::left_shift(size_t shift) const {
    LongInt shifted(*this);
    shifted.digits.insert(shifted.digits.begin(), shift, 0);
    return shifted;
}



LongInt LongInt::karatsuba_multiply(const LongInt& num1, const LongInt& num2) const {
    size_t n = std::max(num1.digits.size(), num2.digits.size());

    if (n == 1) {
        return num1 * num2; 
    }

    size_t m = n / 2;
    LongInt high1, low1, high2, low2;

    high1.digits.assign(num1.digits.begin(), num1.digits.begin() + m);
    low1.digits.assign(num1.digits.begin() + m, num1.digits.end());

    high2.digits.assign(num2.digits.begin(), num2.digits.begin() + m);
    low2.digits.assign(num2.digits.begin() + m, num2.digits.end());

    LongInt z0 = karatsuba_multiply(low1, low2);
    LongInt z1 = karatsuba_multiply(low1 + high1, low2 + high2);
    LongInt z2 = karatsuba_multiply(high1, high2);

    LongInt result = z2 + ((z1 - z2 - z0).left_shift(m)) + (z0.left_shift(2 * m));

    return result;
}

