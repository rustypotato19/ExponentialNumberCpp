#include "../include/number.h"
#include "../include/utils.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "../include/number.h"

// auto-normlising constructor
Number::Number(double m, int e) {
    if (m == 0.0f) {
        mantissa = 0.0f;
        exponent = 0;
    } else {
        int shift = static_cast<int>(floor(log10(fabs(m))));
        mantissa = m / pow(10, shift);
        exponent = e + shift;
    }
}

// Default constructor (needed for vector)
Number::Number() : mantissa(0), exponent(0) {}

/************************
*                       *
*   Helper Functions    *
*                       *
*************************/

// Method to get the number in scientific notation
std::string Number::printNumber() const {
    std::ostringstream oss;

    if (this->mantissa == 0){
        return "0";
    }

    // When exponent >= 6 or <= 2, print in scientific notation
    if (this->exponent >= 6 || this->exponent <= -3) {
        if (floor(mantissa) == mantissa) {
            oss << std::fixed << std::setprecision(0) << mantissa;
        } else {
            oss << std::fixed << std::setprecision(2) << mantissa;
        }
        return oss.str() + "e" + std::to_string(exponent);
    } else {
        double regularNumber = mantissa * pow(10, exponent);

        if (floor(regularNumber) == regularNumber) {
            long long intNum = static_cast<long long>(regularNumber);
            return addCommas(std::to_string(intNum));
        } else {
            oss << std::fixed << std::setprecision(2) << regularNumber;
            std::string raw = oss.str();

            // Split before and after decimal to format only the integer part
            size_t dot = raw.find('.');
            std::string intPart = raw.substr(0, dot);
            std::string fracPart = raw.substr(dot); // includes the dot

            return addCommas(intPart) + fracPart;
        }
    }
}



// Method to convert a double into scientific notation and set mantissa and exponent
Number Number::toNumber(double value) const {
    if (value == 0) {
        return Number(0, 0);
    }

    int exponent = static_cast<int>(floor(log10(fabs(value))));
    double mantissa = value / pow(10, exponent);
    return Number(mantissa, exponent);
}

/************************************
*                                   *
*   Addition Operator Overrides     *
*                                   *
*************************************/

// Overload the "+" operator for Number objects
Number Number::operator+(const Number& other) {
    double newMantissa;
    int newExponent;

    if (this->exponent == other.exponent) {
        newMantissa = this->mantissa + other.mantissa;
        newExponent = this->exponent;
    }
    else if (this->exponent > other.exponent) {
        // Adjust the smaller mantissa based on the exponent difference
        int divider = this->exponent - other.exponent;
        double newOtherMantissa = other.mantissa / pow(10, divider);
        
        newMantissa = this->mantissa + newOtherMantissa;
        newExponent = this->exponent;
    }
    else {
        // Adjust the smaller mantissa based on the exponent difference
        int divider = other.exponent - this->exponent;
        double newThisMantissa = this->mantissa / pow(10, divider);
        
        newMantissa = other.mantissa + newThisMantissa;
        newExponent = other.exponent;
    }

    // Normalize to ensure mantissa stays between [1.0, 10)
    int exponentAdjust = static_cast<int>(floor(log10(fabs(newMantissa))));
    newMantissa /= pow(10, exponentAdjust);
    newExponent += exponentAdjust;

    return Number(newMantissa, newExponent);
}

// Overload the "+=" operator for Number object
Number& Number::operator+=(const Number& other){
    *this = *this + other;
    return *this;
}

// Overload the "+" operator for double
Number Number::operator+(const double other){
    return *this + toNumber(other); 
}

// Overload for Number + int
Number Number::operator+(const int other) {
    // Handle int addition (convert int to Number by treating it as a mantissa)
    return *this + Number(static_cast<double>(other), 0);  // Treat the int as a Number with exponent 0
}

// Overload the "+=" operator for double
Number& Number::operator+=(const double other){
    *this = *this + toNumber(other);
    return *this;
}

/****************************************
*                                       *
*   Subtraction Operator Overrides      *
*                                       *
*****************************************/

Number Number::operator-(const Number& other) {
    double newMantissa;
    int newExponent;

    if (this->exponent == other.exponent) {
        newMantissa = this->mantissa - other.mantissa;
        newExponent = this->exponent;
    }
    else if (this->exponent > other.exponent) {
        int diff = this->exponent - other.exponent;
        double adjustedOtherMantissa = other.mantissa / pow(10, diff);
        newMantissa = this->mantissa - adjustedOtherMantissa;
        newExponent = this->exponent;
    } 
    else {
        int diff = other.exponent - this->exponent;
        double adjustedThisMantissa = this->mantissa / pow(10, diff);
        newMantissa = adjustedThisMantissa - other.mantissa;
        newExponent = other.exponent;
    }

    // Handle zero result
    if (newMantissa == 0.0f) {
        return Number(0.0f, 0);
    }

    // Normalize to ensure mantissa stays between [1.0, 10)
    int exponentAdjust = static_cast<int>(floor(log10(fabs(newMantissa))));
    newMantissa /= pow(10, exponentAdjust);
    newExponent += exponentAdjust;

    return Number(newMantissa, newExponent);
}

Number Number::operator-(const double other){
    return *this - toNumber(other);
}

Number& Number::operator-=(const Number& other) {
    *this = *this - other;
    return *this;
} 

Number& Number::operator-=(const double other){
    *this = *this - toNumber(other);
    return *this; 
}


/****************************************
*                                       *
*   Multiplication Operator Overrides   *
*                                       *
*****************************************/


// Overload the "*" operator for Number object
Number Number::operator*(const Number& other) {
    if (this->mantissa == 0 || other.mantissa == 0){
        return Number(0,0);
    }

    double newMantissa = this->mantissa * other.mantissa;
    int newExponent = this->exponent + other.exponent;

    // Normalize to ensure mantissa stays between [1.0, 10)
    int exponentAdjust = static_cast<int>(floor(log10(fabs(newMantissa))));
    newMantissa /= pow(10, exponentAdjust);
    newExponent += exponentAdjust;

    return Number(newMantissa, newExponent);
}


// Overload the "*=" operator for Number object
Number& Number::operator*=(const Number& other){
    *this = *this * other;
    return *this; 
}


// Overload the "*" operator for double
Number Number::operator*(const double other){
    return *this * toNumber(other); 
}

// Overload the "*=" operator for double
Number& Number::operator*=(const double other){
    *this = *this * toNumber(other);
    return *this; 
}

/************************************
*                                   *
*   Division Operator Overrides     *
*                                   *
*************************************/

// Overload the "/" operator for Number object
Number Number::operator/(const Number& other){
    if (this->mantissa == 0 || other.mantissa == 0){
        if (other.mantissa == 0) std::cerr << "\033[33m[WARN]\033[0m => Division by zero-ish Number. Returned 0e0." << std::endl << "Program attempted: " << this->printNumber() << " / " << other.printNumber() << std::endl;
        return Number(0, 0);
    }

    double newMantissa = this->mantissa / other.mantissa;
    int newExponent = this->exponent - other.exponent;

    // Normalize to ensure mantissa stays between [1.0, 10)
    int exponentAdjust = static_cast<int>(floor(log10(fabs(newMantissa))));
    newMantissa /= pow(10, exponentAdjust);
    newExponent += exponentAdjust;

    return Number(newMantissa, newExponent);
}

// Overload the "/=" operator for Number object
Number Number::operator/(const double other){
    return *this / toNumber(other);
}

// Overload the "/=" operator for double
Number& Number::operator/=(const Number& other){
    *this = *this / other;
    return *this;
}

// Overload the "/=" operator for double
Number& Number::operator/=(const double other){
    *this = *this / toNumber(other);
    return *this;
}

/************************************
*                                   *
*   Comparative Operator Overrides  *
*                                   *
*************************************/

// ----- == operator -----

bool Number::operator==(const Number& other){
    return (this->mantissa == other.mantissa) && (this->exponent == other.exponent);
}

bool Number::operator==(const double other){
    return *this == toNumber(other);
}

// ----- != operator -----

bool Number::operator!=(const Number& other){
    return !(*this == other);
}

bool Number::operator!=(const double other){
    return !(*this == toNumber(other));
}

// ----- < operator -----

bool Number::operator<(const Number& other){
    if (this->exponent == other.exponent){
        return this->mantissa < other.mantissa;
    }
    else {
        return this->exponent < other.exponent;
    }
}

bool Number::operator<(const double other){
    return *this < toNumber(other);
}

// ----- <= operator -----

bool Number::operator<=(const Number& other){
    return (*this < other) || (*this == other);
}

bool Number::operator<=(const double other){
    return (*this < toNumber(other)) || (*this == toNumber(other));
}

// ----- > operator -----

bool Number::operator>(const Number& other){
    if (this->exponent == other.exponent){
        return this->mantissa > other.mantissa;
    }
    else {
        return this->exponent > other.exponent;
    }
}

bool Number::operator>(const double other){
    return *this > toNumber(other);
}

// ----- >= operator -----

bool Number::operator>=(const Number& other){
    return (*this > other) || (*this == other);
}

bool Number::operator>=(const double other){
    return (*this > toNumber(other)) || (*this == toNumber(other));
}
    