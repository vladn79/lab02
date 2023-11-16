// LongInt.cpp
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
