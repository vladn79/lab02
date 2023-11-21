#pragma once
#include <vector>
#include <iostream>

class LongInt {
private:
    std::vector<int> digits;

public:
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

    LongInt left_shift(size_t shift) const;
    LongInt karatsuba_multiply(const LongInt& num1, const LongInt& num2) const;
    LongInt toom_cook_multiply(const LongInt& num1, const LongInt& num2) const;
     
    friend std::ostream& operator<<(std::ostream& out, LongInt num);
    friend std::istream& operator>>(std::istream& in, LongInt& num);
};