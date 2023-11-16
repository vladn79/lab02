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

    LongInt karatsubaMultiply(const LongInt& x, const LongInt& y) const;
    LongInt karatsubaMultiply(const LongInt& other) const;


    friend std::ostream& operator<<(std::ostream& out, LongInt num);
    friend std::istream& operator>>(std::istream& in, LongInt& num);
};
