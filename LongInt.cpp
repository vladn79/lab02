#include "LongInt.h"
#include <algorithm>
using namespace std;
int base = 10;

LongInt::LongInt(std::string x) {
    value = std::move(x);
}

LongInt::LongInt() {
    value = "0";
}

long LongInt::alignStrings(std::string& num1, std::string& num2) {
    long n = std::max(num1.size(), num2.size());

    while (num1.size() < n)
        num1.insert(0, "0");

    while (num2.size() < n)
        num2.insert(0, "0");

    return n;
}

std::string LongInt::add(std::string num1, std::string num2) {
           int spare = 0;
        long n = alignStrings(num1, num2);
        string res;
        int sum;

        for (int i = n - 1; i >= 0; i--) {
            sum = (num1[i] - '0') + (num2[i] - '0') + spare;
            res.insert(0, to_string(sum % base));
            spare = sum / base;
        }

        if (spare) {
            res.insert(0, to_string(spare));
        }

        return res.erase(0, min(res.find_first_not_of('0'), res.size() - 1));
}

std::string LongInt::sub(std::string num1, std::string num2) {
        int diff;
        long n = alignStrings(num1, num2);
        string x, y, res;

        if (num1 > num2) {
            x = num1;
            y = num2;
        }
        else {
            x = num2;
            y = num1;
        }

        for (int i = n - 1; i >= 0; i--) {
            diff = (x[i] - '0') - (y[i] - '0');

            if (diff >= 0)
                res.insert(0, to_string(diff));

            else {
                int prev = i - 1;
                while (prev >= 0) {
                    x[prev] = (base + (x[prev] - '0') - 1) % base + '0';

                    if (x[prev] != '9')
                        break;
                    else
                        prev--;
                }
                res.insert(0, to_string(diff + base));
            }
        }
        return res.erase(0, min(res.find_first_not_of('0'), res.size() - 1));
}

std::string LongInt::multiplyByPowerOf10(std::string& num, long times) {
        
        for (int k = 0; k < times; k++)
            num.append("0");

        return num;
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
LongInt& LongInt::operator=(std::string x) {
    *this = LongInt(std::move(x));
    return *this;
}

LongInt LongInt::operator+(const LongInt& x) {
    return LongInt(add(value, x.value));
}

LongInt LongInt::operator-(const LongInt& x) {
    return LongInt(sub(value, x.value));
}

LongInt LongInt::operator*(int multiplier) {
    LongInt result = *this;
    for (int i = 1; i < multiplier; ++i) {
        result = result + *this;
    }
    return result;
}

LongInt LongInt::operator%(const LongInt& x) {
    LongInt quotient, remainder, temp;
    LongInt dividend = *this;

    while (dividend >= x) {
        temp = x;
        LongInt current_quotient = "1"s;

        while (dividend >= temp) {
            dividend = dividend - temp;
            quotient = quotient + current_quotient;

            temp = temp * 10;
            current_quotient = current_quotient * 10;
        }
    }

    remainder = dividend;
    return remainder;
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

std::string LongInt::karatsuba_multiply(LongInt num1, LongInt num2) {
        LongInt res, a0, a1, b0, b1, m1, m2, c1, c2, c1_c2, Z1;
        long n = LongInt::alignStrings(num1.value, num2.value);

        if (n == 1) {
            return to_string((num1.value[0] - '0') * (num2.value[0] - '0'));
        }

        a0 = num1.value.substr(0, n / 2);
        a1 = num1.value.substr(n / 2, n - n / 2);
        b0 = num2.value.substr(0, n / 2);
        b1 = num2.value.substr(n / 2, n - n / 2);

        m1 = karatsuba_multiply(a0, b0);
        m2 = karatsuba_multiply(a1, b1);
        c1 = (a0 + a1);
        c2 = (b0 + b1);
        c1_c2 = karatsuba_multiply(c1, c2);
        Z1 = c1_c2 - m1 - m2;

        LongInt::multiplyByPowerOf10(m1.value, 2 * (n - n / 2));
        LongInt::multiplyByPowerOf10(Z1.value, (n - n / 2));

        res = m1 + m2 + Z1;

        return res.value.erase(0, min(res.value.find_first_not_of('0'), res.value.size() - 1));
}

std::string LongInt::toom_cook_multiply(LongInt num1, LongInt num2) {

        LongInt res, a0, a1, a2, b0, b1, b2, m1, m2, m0, c1, c2, c3, m01, m02, m12;
        long l = LongInt::alignStrings(num1.value, num2.value);

        if (l == 1) {
            return to_string((num1.value[0] - '0') * (num2.value[0] - '0'));
        }

        if (l % 3) {
            l += 3 - l % 3;
            while (num1.value.size() < l)
                num1.value.insert(0, "0");
            LongInt::alignStrings(num1.value, num2.value);
        }

        a0 = num1.value.substr(0, l / 3);
        a1 = num1.value.substr(l / 3, l / 3);
        a2 = num1.value.substr(2 * l / 3, l / 3);
        b0 = num2.value.substr(0, l / 3);
        b1 = num2.value.substr(l / 3, l / 3);
        b2 = num2.value.substr(2 * l / 3, l / 3);

        m0 = toom_cook_multiply(a0, b0);
        m1 = toom_cook_multiply(a1, b1);
        m2 = toom_cook_multiply(a2, b2);

        c1 = toom_cook_multiply((a0 + a1), (b0 + b1));
        c2 = toom_cook_multiply((a0 + a2), (b0 + b2));
        c3 = toom_cook_multiply((a1 + a2), (b1 + b2));
        
        m01 = c1 - m0 - m1;
        m02 = c2 - m0 - m2;
        m12 = c3 - m1 - m2;

        m0 = LongInt::multiplyByPowerOf10(m0.value, 4 * l / 3);
        m01 = LongInt::multiplyByPowerOf10(m01.value, 3 * l / 3);
        m1 = LongInt::multiplyByPowerOf10(m1.value, 2 * l / 3);
        m02 = LongInt::multiplyByPowerOf10(m02.value, 2 * l / 3);
        m12 = LongInt::multiplyByPowerOf10(m12.value, l / 3);

        res = m0 + m1 + m2 + m01 + m02 + m12;

        return res.value.erase(0, min(res.value.find_first_not_of('0'), res.value.size() - 1));
}