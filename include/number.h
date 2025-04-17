#ifndef NUMBER_H
#define NUMBER_H

#include <string>

class Number {
public:
    double mantissa;
    int exponent;

    Number(double m, int e);

    Number();

    std::string printNumber() const;
    Number toNumber(double value) const;

    // Operator Overloads
    Number operator+(const Number& other);
    Number& operator+=(const Number& other);
    Number operator+(const double other);
    Number& operator+=(const double other);
    Number operator+(const int other);

    Number operator-(const Number& other);
    Number operator-(const double other);
    Number& operator-=(const Number& other);
    Number& operator-=(const double other);

    Number operator*(const Number& other);
    Number operator*(const double other);
    Number& operator*=(const Number& other);
    Number& operator*=(const double other);

    Number operator/(const Number& other);
    Number operator/(const double other);
    Number& operator/=(const Number& other);
    Number& operator/=(const double other);

    bool operator==(const Number& other);
    bool operator==(const double other);
    bool operator!=(const Number& other);
    bool operator!=(const double other);
    bool operator<(const Number& other);
    bool operator<(const double other);
    bool operator<=(const Number& other);
    bool operator<=(const double other);
    bool operator>(const Number& other);
    bool operator>(const double other);
    bool operator>=(const Number& other);
    bool operator>=(const double other);
};

#endif // NUMBER_H
