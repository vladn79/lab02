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

LongInt LongInt::operator%(const LongInt& other) const {
    LongInt result(*this);
    LongInt divisor(other);
    if (divisor < LongInt("0")) {
        divisor = divisor * LongInt("-1");
    }

    while (result >= divisor) {
        int borrow = 0;

        for (int i = 0; i < divisor.digits.size(); ++i) {
            int diff = result.digits[i] - borrow;
            if (i < divisor.digits.size()) {
                diff -= divisor.digits[i];
            }
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.digits[i] = diff;
        }
        while (result.digits.size() > 1 && result.digits.back() == 0) {
            result.digits.pop_back();
        }
    }

    return result;
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

LongInt LongInt::toom_cook_multiply(const LongInt& num1, const LongInt& num2) const {
    size_t n = std::max(num1.digits.size(), num2.digits.size());
    if (n <= 3) {
        return num1 * num2;
    }
    size_t m = n / 3;
    LongInt low1, mid1, high1, low2, mid2, high2;

    low1.digits.assign(num1.digits.begin(), num1.digits.begin() + m);
    mid1.digits.assign(num1.digits.begin() + m, num1.digits.begin() + 2 * m);
    high1.digits.assign(num1.digits.begin() + 2 * m, num1.digits.end());

    low2.digits.assign(num2.digits.begin(), num2.digits.begin() + m);
    mid2.digits.assign(num2.digits.begin() + m, num2.digits.begin() + 2 * m);
    high2.digits.assign(num2.digits.begin() + 2 * m, num2.digits.end());

    LongInt z0 = toom_cook_multiply(low1, low2);
    LongInt z4 = toom_cook_multiply(high1, high2);

    LongInt low1_plus_mid1 = low1 + mid1;
    LongInt low2_plus_mid2 = low2 + mid2;

    LongInt z2 = toom_cook_multiply(low1_plus_mid1, low2_plus_mid2);
    LongInt z3 = toom_cook_multiply(mid1 + high1, mid2 + high2);

    LongInt mid_term = z2 + z3 - z0 - z4;
    LongInt z1 = mid_term.left_shift(m);

    LongInt result = z0 + z1 + z2.left_shift(2 * m) + z3.left_shift(3 * m) + z4.left_shift(4 * m);

    return result;
} 







