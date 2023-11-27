#pragma once
#include <string>
#include <vector>
#include <complex>
class LongInt {
public:
    std::string value;
    std::vector<int> coefficients;
    
    LongInt(std::string x);
    LongInt(int n);
    LongInt();
    LongInt(const std::vector<int>& coeffs) : coefficients(coeffs) {}

    static long alignStrings(std::string& num1, std::string& num2);
    static std::string add(std::string num1, std::string num2);
    static std::string sub(std::string num1, std::string num2);
    static std::string multiplyByPowerOf10(std::string& num, long times);


    bool operator ==(const LongInt& other);
    bool operator !=(const LongInt& other);
    bool operator >(const LongInt& other);
    bool operator <=(const LongInt& other);
    bool operator >=(const LongInt& other);
    bool operator <(const LongInt& other);

    LongInt& operator=(std::string x);
    LongInt operator+(const LongInt& x);
    LongInt operator-(const LongInt& x);
    LongInt operator*(const LongInt& other) const;
    LongInt operator*(int n) const;
    LongInt operator/(int n) const;
    LongInt operator/(const LongInt& other) const;
    LongInt operator%(const LongInt& other) const;
    LongInt operator%(int n) const;

    static std::string karatsuba_multiply(LongInt num1, LongInt num2);
    static std::string toom_cook_multiply(LongInt num1, LongInt num2);
    static std::string shenhageMultiply(LongInt num1, LongInt num2);
    static LongInt schonhageStrassenMultiply(const LongInt& operandA, const LongInt& operandB);


    friend std::ostream& operator<<(std::ostream& out, LongInt num);
    friend std::istream& operator>>(std::istream& in, LongInt& num);

    static void fft(std::vector<std::complex<double>>& a, bool invert);
};