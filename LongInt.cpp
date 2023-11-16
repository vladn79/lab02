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
LongInt LongInt::karatsubaMultiply(const LongInt& x, const LongInt& y) const {

    if (x.digits.size() <= 1 || y.digits.size() <= 1) {
        return x * y;
    }

   
    size_t n = std::max(x.digits.size(), y.digits.size());
    size_t m = (n + 1) / 2;

    LongInt xLow, xHigh, yLow, yHigh;

    for (size_t i = 0; i < m; ++i) {
        xLow.digits.push_back(i < x.digits.size() ? x.digits[i] : 0);
        xHigh.digits.push_back(i + m < x.digits.size() ? x.digits[i + m] : 0);

        yLow.digits.push_back(i < y.digits.size() ? y.digits[i] : 0);
        yHigh.digits.push_back(i + m < y.digits.size() ? y.digits[i + m] : 0);
    }


    LongInt z0 = karatsubaMultiply(xLow, yLow);
    LongInt z1 = karatsubaMultiply(xHigh, yHigh);
    LongInt z2 = karatsubaMultiply(xLow + xHigh, yLow + yHigh) - z0 - z1;

  
    for (size_t i = 0; i < 2 * m; ++i) {
        z0.digits.push_back(0);
    }

    for (size_t i = 0; i < m; ++i) {
        z2.digits.push_back(0);
    }

    return z0 + z1 + z2;
}

LongInt LongInt::karatsubaMultiply(const LongInt& other) const {
    return karatsubaMultiply(*this, other);
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