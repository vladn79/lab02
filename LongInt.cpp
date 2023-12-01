#include "LongInt.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdlib> 
#include <ctime>
using namespace std;
int base = 10;

LongInt::LongInt(std::string x) {
    value = std::move(x);
}

LongInt::LongInt() {
    value = "0";
}

LongInt::LongInt(int n) {
    value = std::to_string(n);
}


long LongInt::alignStrings(std::string& num1, std::string& num2) {
    long n = std::max(num1.size(), num2.size());

    while (num1.size() < n)
        num1.insert(0, "0");

    while (num2.size() < n)
        num2.insert(0, "0");

    return n;
}


long LongInt::alignStrings(const std::string& num1, const std::string& num2) {
    long n = std::max(num1.size(), num2.size());

    std::string alignedNum1 = num1;
    std::string alignedNum2 = num2;

    while (alignedNum1.size() < n)
        alignedNum1.insert(0, "0");

    while (alignedNum2.size() < n)
        alignedNum2.insert(0, "0");

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
LongInt LongInt::operator-(const LongInt& x) const {
    return LongInt(sub(value, x.value));
}

LongInt LongInt::operator*(const LongInt& other) const {
    return LongInt(karatsuba_multiply(*this, other));
}

LongInt LongInt::operator*(int n) const {
    return *this * LongInt(std::to_string(n));
}

bool LongInt::operator ==(const LongInt& other) const {
    return value == other.value;
}


bool LongInt::operator <(const LongInt& other) const {
    if (value.size() != other.value.size()) {
        return value.size() < other.value.size();
    }
    for (int i = int(value.size()) - 1; i >= 0; --i) {
        if (value[i] < other.value[i]) {
            return true;
        } else if (value[i] > other.value[i]) {
            return false;
        }
    }
    return false;
}
bool LongInt::operator>(const LongInt& other) const {
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

LongInt LongInt::operator/(int n) const {
    if (n == 0) {
        return LongInt("0");
    }

    LongInt result;
    std::string quotient;
    long long carry = 0;

    for (char digit : value) {
        long long currentDigit = digit - '0' + carry * base;
        carry = currentDigit % n;
        currentDigit /= n;
        quotient.push_back(static_cast<char>(currentDigit + '0'));
    }

    quotient.erase(0, min(quotient.find_first_not_of('0'), quotient.size() - 1));
    result.value = quotient.empty() ? "0" : quotient;

    return result;
}

LongInt LongInt::operator/(const LongInt& other) const {
    if (other.value == "0") {
        return LongInt("0");
    }

    LongInt quotient;
    LongInt dividend(value);
    LongInt divisor(other.value);

    bool negativeResult = (dividend.value[0] == '-' && divisor.value[0] != '-') || (dividend.value[0] != '-' && divisor.value[0] == '-');
    dividend.value.erase(0, min(dividend.value.find_first_not_of('-'), dividend.value.size() - 1));
    divisor.value.erase(0, min(divisor.value.find_first_not_of('-'), divisor.value.size() - 1));

    LongInt currentDividend;
    for (size_t i = 0; i < dividend.value.size(); ++i) {
        currentDividend = currentDividend * 10 + LongInt(dividend.value[i] - '0');
        int count = 0;

        while (currentDividend >= divisor) {
            currentDividend = currentDividend - divisor;
            count++;
        }

        quotient = quotient * 10 + LongInt(count);
    }
    if (negativeResult) {
        quotient.value.insert(0, "-");
    }

    return quotient;
}

LongInt LongInt::operator%(const LongInt& other) const {
    if (other.value == "0") {
        return LongInt("0");
    }

    LongInt dividend(value);
    LongInt divisor(other.value);

    bool negativeResult = (dividend.value[0] == '-' && divisor.value[0] != '-') || (dividend.value[0] != '-' && divisor.value[0] == '-');
    dividend.value.erase(0, min(dividend.value.find_first_not_of('-'), dividend.value.size() - 1));
    divisor.value.erase(0, min(divisor.value.find_first_not_of('-'), divisor.value.size() - 1));

    LongInt currentDividend;
    for (size_t i = 0; i < dividend.value.size(); ++i) {
        currentDividend = currentDividend * 10 + LongInt(dividend.value[i] - '0');

        while (currentDividend >= divisor) {
            currentDividend = currentDividend - divisor;
        }
    }
    if (negativeResult) {
        currentDividend.value.insert(0, "-");
    }

    return currentDividend;
}


LongInt LongInt::operator%(int n) const {
    if (n == 0) {
        return LongInt("0");
    }

    LongInt result;
    long long remainder = 0;

    for (int i = value.size() - 1; i >= 0; --i) {
        long long currentDigit = value[i] - '0' + remainder * base;
        remainder = currentDigit % n;
    }

    result.value = std::to_string(remainder);

    return result;
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
std::string LongInt::shenhageMultiply(LongInt num1, LongInt num2) {
    LongInt result = LongInt(karatsuba_multiply(num1, num2)) % LongInt("12312312312312312312312312313231231231231231231231231231231231231231231231231231231231231231231231123123");
    return result.value;
}


LongInt LongInt::schonhageStrassenMultiply(const LongInt& operandA, const LongInt& operandB) {
    std::vector<int> coeffsA = operandA.coefficients;
    std::vector<int> coeffsB = operandB.coefficients;

    size_t newSize = 1;
    while (newSize < std::max(coeffsA.size(), coeffsB.size())) {
        newSize *= 2;
    }
    coeffsA.resize(newSize);
    coeffsB.resize(newSize);
    std::vector<int> resultCoefficients(newSize * 2, 0);


    std::vector<std::complex<double>> a(newSize * 2, 0);
    for (size_t i = 0; i < newSize; ++i) {
        a[i] = coeffsA[i];
    }
    fft(a, false);

    std::vector<std::complex<double>> b(newSize * 2, 0);
    for (size_t i = 0; i < newSize; ++i) {
        b[i] = coeffsB[i];
    }
    fft(b, false);


    for (size_t i = 0; i < a.size(); ++i) {
        a[i] *= b[i];
    }


    fft(a, true);


    for (size_t i = 0; i < resultCoefficients.size(); ++i) {
        resultCoefficients[i] = static_cast<int>(std::round(a[i].real()));
    }

    for (size_t i = 0; i < resultCoefficients.size() - 1; ++i) {
        resultCoefficients[i + 1] += resultCoefficients[i] / 10;
        resultCoefficients[i] %= 10;
    }
    
    return LongInt(resultCoefficients);
}



void LongInt::fft(std::vector<std::complex<double>>& a, bool invert) {
    const double PI = invert ? -acos(-1) : acos(-1);
    const size_t n = a.size();

    if (n <= 1) {
        return;
    }

    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (size_t i = 0, j = 0; i < n; i += 2, ++j) {
        a0[j] = a[i];
        a1[j] = a[i + 1];
    }

    fft(a0, invert);
    fft(a1, invert);

    for (size_t i = 0; i < n / 2; ++i) {
        std::complex<double> t = std::polar(1.0, -2 * PI * i / n) * a1[i];
        a[i] = a0[i] + t;
        a[i + n / 2] = a0[i] - t;
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
    }
}


 auto LongInt::rbegin() const {
        return value.rbegin();
    }

auto LongInt::rend() const {
        return value.rend();
    }
void LongInt::removeLeadingZero() {
        auto nonZeroPos = std::find_if_not(coefficients.rbegin(), coefficients.rend(), [](int digit) {
            return digit == 0;
        });
        coefficients.erase(nonZeroPos.base(), coefficients.end());  
    }



bool LongInt::isPrimeFermat(LongInt n, int iterations) {
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;

    for (int i = 0; i < iterations; ++i) {

        LongInt a("2");
        a = a + LongInt("2") + LongInt(rand()) % (n - 3);


        if (n.power(a, n - 1, n) != 1)
            return false;
    }

    return true;
}

LongInt LongInt::power(const LongInt& a, const LongInt& b, const LongInt& mod) const {
    LongInt result("1");
    LongInt base = a % mod;
    LongInt exponent = b;

    while (exponent > LongInt("0")) {
        if (exponent % LongInt("2") == LongInt("1"))
            result = (result * base) % mod;
        exponent = exponent / LongInt("2");
        base = (base * base) % mod;
    }

    return result;
}

bool LongInt::millerRabinTest(LongInt& n, int iterations) {
    if (n <= 1 || n == 4)
        return false;
    if (n <= 3)
        return true;
    LongInt d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d = d / LongInt("2");
        s++;
    }
    for (int i = 0; i < iterations; ++i) {
        LongInt a("2");
         a = LongInt("2") +LongInt(rand()) % (n - 3);
        LongInt x = power(a, d, n);
        if (x == 1 || x == n - 1)
            continue;
        for (int r = 1; r < s; r++) {
            x = (x * x) % n;
            if (x == 1)
                return false; 
            if (x == n - 1)
                break; 
        }

        if (x != n - 1)
            return false; 
    }
    return true;
}

LongInt LongInt::jacobi(LongInt& n, LongInt& k) {
    n  = n % k;
    int t = 1;

    while (n != 0) {
        while (n % 2 == 0) {
            n = n / 2;
            LongInt r = k % LongInt("8");

            if (r == 3 || r == 5) {
                t = -t;
            }
        }
        std::swap(n, k);
        if (n % 4 == 3 && k % 4 == 3) {
            t = -t;
        }
        n = n % k;
    }
    if (k == 1) {
        return t;
    } else {
        return 0;
    }
}

bool LongInt::Solovey_Str(LongInt& n, int k) {
    LongInt a, p, r;
    for (int i = 0; i < k; ++i) {
        a = LongInt(rand()) % (n - 2) + LongInt("2");
        p = (n - 1) / 2;
        r = power(a, p, n);

        LongInt j = jacobi(a, n);

        if (r != j % n && (r + n) % n != j % n) {
            return false;
        }
    }
    return true;
}