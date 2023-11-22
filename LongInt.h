#pragma once
#include <iostream>

class LongInt {

public:
    std::string value;
    LongInt();
    LongInt(const std::string& numStr);

    bool operator ==(const LongInt& other);
    bool operator !=(const LongInt& other);
    bool operator >(const LongInt& other);
    bool operator <=(const LongInt& other);
    bool operator >=(const LongInt& other);
    bool operator <(const LongInt& other);

    LongInt operator+(const LongInt& other);
    LongInt operator-(const LongInt& other) const;
    LongInt operator*(const LongInt& other) const;
    LongInt operator%(const LongInt& other) const;

    std::string getValue() const;
    std::string toString() const {
        return value;
    }

    friend std::ostream& operator<<(std::ostream& out, LongInt num);
    friend std::istream& operator>>(std::istream& in, LongInt& num);

    long alignStrings(std::string& num1, std::string& num2);
    LongInt multiplyByPowerOf10(const LongInt& num, long times);


   LongInt karatsuba_multiply(const LongInt& num1, const LongInt& num2);
};