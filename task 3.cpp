#include <algorithm>
#include <iostream>
#include <numeric> 
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

#include <stdint.h>

class Rational {
    long long gcd(long long a, long long b) {
        a = std::abs(a);
        b = std::abs(b);
        while (b != 0) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void normal() {
        if (q < 0) {
            q = -q;
            p = -p;
        }
        long long new_gcd = gcd(std::abs(p), std::abs(q));
        p = p / new_gcd;
        q = q / new_gcd;
    }

public:
    long long p;
    long long q;

    Rational(long long numerator, long long denominator = 1) : p(numerator), q(denominator) {
        if (q == 0) {
            throw std::invalid_argument("Division by zero!");
        }
        normal();
    }

    operator double() const {
        return static_cast<double>(p) / q;
    }

    Rational operator+=(const Rational& other) {
        long long num = p * other.q + q * other.p;
        long long delit = q * other.q;
        p = num;
        q = delit;
        normal();
        return *this;
    }

    Rational operator-=(const Rational& other) {
        long long num = p * other.q - q * other.p;
        long long delit = q * other.q;
        p = num;
        q = delit;
        normal();
        return *this;
    }

    Rational operator*=(const Rational& other) {
        long long num = p * other.p;
        long long delit = q * other.q;
        p = num;
        q = delit;
        normal();
        return *this;
    }

    Rational operator/=(const Rational& other) {
        if (other.p == 0) {
            throw std::invalid_argument("Division by zero!");
        }
        long long num = p * other.q;
        long long delit = q * other.p;
        p = num;
        q = delit;
        normal();
        return *this;
    }

    Rational operator+(const Rational& other) const {
        long long num = p * other.q + q * other.p;
        long long delit = q * other.q;
        return Rational(num, delit);
    }

    Rational operator-(const Rational& other) const {
        long long num = p * other.q - q * other.p;
        long long delit = q * other.q;
        return Rational(num, delit);
    }

    Rational operator*(const Rational& other) const {
        long long num = p * other.p;
        long long delit = q * other.q;
        return Rational(num, delit);
    }

    Rational operator/(const Rational& other) const {
        if (other.p == 0) {
            throw std::invalid_argument("Division by zero!");
        }
        long long num = p * other.q;
        long long delit = q * other.p;
        return Rational(num, delit);
    }

    Rational operator++(int) {
        Rational last = *this;
        p += q;
        normal();
        return last;
    }
    Rational operator--(int) {
        Rational last = *this;
        p -= q;
        normal();
        return last;
    }

    Rational operator++() {
        p += q;
        normal();
        return *this;
    }

    Rational operator--() {
        p -= q;
        normal();
        return *this;
    }

    Rational& operator=(const Rational& other) {
        p = other.p;
        q = other.q;
        return *this;
    }

    bool operator<(const Rational& other) const {
        if (p * other.q - q * other.p < 0) {
            return true;
        }
        return false;
    }

    bool operator>(const Rational& other) const {
        if (p * other.q - q * other.p > 0) {
            return true;
        }
        return false;
    }

    bool operator>=(const Rational& other) const {
        if (p * other.q - q * other.p >= 0) {
            return true;
        }
        return false;
    }

    bool operator<=(const Rational& other) const {
        if (p * other.q - q * other.p <= 0) {
            return true;
        }
        return false;
    }

    bool operator==(const Rational& other) const {
        if (p * other.q - q * other.p == 0) {
            return true;
        }
        return false;
    }

    bool operator!=(const Rational& other) const {
        if (p * other.q - q * other.p != 0) {
            return true;
        }
        return false;
    }
};
std::istream& operator>>(std::istream& in, Rational& r) {
    std::string new_r;
    in >> new_r;
    std::stringstream ss(new_r);
    std::string part;

    std::getline(ss, part, '/');
    r.p = std::stoi(part);
    std::getline(ss, part, '/');
    r.q = std::stoi(part);
    return in;
}
std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.p << "/" << r.q;
    return os;
}