#pragma once
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std::string_literals;

class LongInt {
public:
    std::string value;
    
    LongInt(std::string x);
    LongInt();

    static long alignStrings(std::string& num1, std::string& num2);
    static std::string add(std::string num1, std::string num2);
    static std::string sub(std::string num1, std::string num2);
    static std::string multiplyByPowerOf10(std::string& num, long times);


    bool operator ==(const LongInt& other) const;
    bool operator !=(const LongInt& other);
    bool operator >(const LongInt& other);
    bool operator <=(const LongInt& other);
    bool operator >=(const LongInt& other);
    bool operator <(const LongInt& other);

    LongInt& operator=(std::string x);
    LongInt operator+(const LongInt& x);
    LongInt operator-(const LongInt& x) const;
    LongInt operator*(int multiplier);
    LongInt operator%(const LongInt& x) const;
    LongInt operator/(int n) const;

    


    static std::string karatsuba_multiply(LongInt num1, LongInt num2);
    static std::string toom_cook_multiply(LongInt num1, LongInt num2);


    friend std::ostream& operator<<(std::ostream& out, const LongInt& num);
    friend std::istream& operator>>(std::istream& in, LongInt& num);


    LongInt pow_mod(const LongInt &other, const LongInt &modulus) const;
    bool ferma() const;

};

class Rand {
    LongInt xn;
    int a = 11;
    LongInt c = LongInt("1");
    LongInt m;
public:
    Rand(int seed = 2, LongInt m = LongInt("1000000000000123123123123123123123123123234342453245245600"));
    LongInt next();
};
