#include "LongInt.h"
#include <algorithm>

LongInt::LongInt() {}

LongInt::LongInt(const std::string& numStr) {
    for (auto it = numStr.rbegin(); it != numStr.rend(); ++it) {
        if (std::isdigit(*it)) {
            value.push_back(*it);
        }
    }
}

bool LongInt::operator==(const LongInt& other) {
    return value == other.value;
}

bool LongInt::operator!=(const LongInt& other) {
    return !(operator==(other));
}

bool LongInt::operator>(const LongInt& other) {
    if (value.size() != other.value.size()) {
        return value.size() > other.value.size();
    }
    for (int i = int(value.size()) - 1; i >= 0; --i) {
        if (value[i] > other.value[i]) {
            return true;
        } else if (value[i] < other.value[i]) {
            return false;
        }
    }
    return false; 
}

bool LongInt::operator<=(const LongInt& other) {
    return !(operator>(other));
}

bool LongInt::operator>=(const LongInt& other) {
    return (operator>(other) || operator==(other));
}

bool LongInt::operator<(const LongInt& other) {
    return !(operator>=(other));
}


std::string LongInt::getValue() const {
    return value;
}


std::ostream& operator<<(std::ostream& out, const LongInt& num) {
    out << num.value;
    return out;
}

std::istream& operator>>(std::istream& in, LongInt& num) {
    std::string input;
    in >> input;
    num = LongInt(input);
    return in;
}


LongInt LongInt::operator+(const LongInt& other) {
    LongInt result;

    int carry = 0;
    size_t maxLength = std::max(value.size(), other.value.size());

    for (size_t i = 0; i < maxLength || carry; ++i) {
        int sum = carry + (i < value.size() ? value[i] - '0' : 0) + (i < other.value.size() ? other.value[i] - '0' : 0);
        carry = sum / 10;
        result.value.push_back(sum % 10 + '0');
    }
    std::reverse(result.value.begin(), result.value.end());

    return result;
}

LongInt LongInt::operator-(const LongInt& other) const {
    LongInt result;
    int borrow = 0;
    int maxSize = std::max(value.size(), other.value.size());

    for (int i = 0; i < maxSize; ++i) {
        int diff = (i < value.size() ? value[i] - '0' : 0) - borrow;
        if (i < other.value.size()) {
            diff -= other.value[i] - '0';
        }
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.value.push_back(diff + '0');
    }
    std::reverse(result.value.begin(), result.value.end());
    while (result.value.size() > 1 && result.value.front() == '0') {
        result.value.erase(result.value.begin());
    }

    return result;
}


long LongInt::alignStrings(std::string& num1, std::string& num2) {
    long n = std::max(num1.size(), num2.size());

    while (num1.size() < n)
        num1.insert(0, "0");

    while (num2.size() < n)
        num2.insert(0, "0");

    return n;
}




LongInt LongInt::multiplyByPowerOf10(const LongInt& num, long times) {
    LongInt result = num;
    for (int k = 0; k < times; k++) {
        result.value.append("0");
    }
    return result;
}

LongInt LongInt::karatsuba_multiply(const LongInt& num1, const LongInt& num2) {
    LongInt res, a0, a1, b0, b1, m1, m2, c1, c2, c1_c2, Z1;
    long n = alignStrings(a0.value, b0.value);

    if (n == 1) {
        return std::to_string((a0.value[0] - '0') * (b0.value[0] - '0'));
    }

    a1.value = a0.value.substr(n / 2);
    a0.value = a0.value.substr(0, n / 2);
    b1.value = b0.value.substr(n / 2);
    b0.value = b0.value.substr(0, n / 2);

    m1 = karatsuba_multiply(a0, b0);
    m2 = karatsuba_multiply(a1, b1);
    c1 = a0 + a1;
    c2 = b0 + b1;
    c1_c2 = karatsuba_multiply(c1, c2);
    Z1 = c1_c2 - m1 - m2;

    m1 = multiplyByPowerOf10(m1, 2 * (n / 2));
    Z1 = multiplyByPowerOf10(Z1, (n / 2));  

    res = m1 + m2 + Z1;
    return LongInt(res.getValue().erase(0, res.getValue().find_first_not_of('0')));
}













