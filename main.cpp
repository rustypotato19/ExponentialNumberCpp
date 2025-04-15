#include "main.h"

using namespace std;

class Number {
public:
    double mantissa;
    int exponent;

    // auto-normlising constructor
    Number(double m, int e) {
        if (m == 0.0f) {
            mantissa = 0.0f;
            exponent = 0;
        } else {
            int shift = static_cast<int>(floor(log10(fabs(m))));
            mantissa = m / pow(10, shift);
            exponent = e + shift;
        }
    }
    

    /************************
    *                       *
    *   Helper Functions    *
    *                       *
    *************************/

    // Method to get the number in scientific notation
    string printNumber() const {
        ostringstream oss;

        if (this->mantissa == 0){
            return "0";
        }
    
        // When exponent >= 6 or <= 2, print in scientific notation
        if (this->exponent >= 6 || this->exponent <= -3) {
            if (floor(mantissa) == mantissa) {
                oss << fixed << setprecision(0) << mantissa;
            } else {
                oss << fixed << setprecision(2) << mantissa;
            }
            return oss.str() + "e" + to_string(exponent);
        } else {
            double regularNumber = mantissa * pow(10, exponent);
    
            if (floor(regularNumber) == regularNumber) {
                long long intNum = static_cast<long long>(regularNumber);
                return addCommas(to_string(intNum));
            } else {
                oss << fixed << setprecision(2) << regularNumber;
                string raw = oss.str();
    
                // Split before and after decimal to format only the integer part
                size_t dot = raw.find('.');
                string intPart = raw.substr(0, dot);
                string fracPart = raw.substr(dot); // includes the dot
    
                return addCommas(intPart) + fracPart;
            }
        }
    }
    


    // Method to convert a double into scientific notation and set mantissa and exponent
    Number toNumber(double value) const {
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
    Number operator+(const Number& other) {
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
    Number& operator+=(const Number& other){
        *this = *this + other;
        return *this;
    }

    // Overload the "+" operator for double
    Number operator+(const double other){
        return *this + toNumber(other); 
    }

    
    // Overload the "+=" operator for double
    Number& operator+=(const double other){
        *this = *this + toNumber(other);
        return *this;
    }

    /****************************************
    *                                       *
    *   Subtraction Operator Overrides      *
    *                                       *
    *****************************************/

    Number operator-(const Number& other) {
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

    Number operator-(const double other){
        return *this - toNumber(other);
    }

    Number& operator-=(const Number& other) {
        *this = *this - other;
        return *this;
    } 

    Number& operator-=(const double other){
        *this = *this - toNumber(other);
        return *this; 
    }
    

    /****************************************
    *                                       *
    *   Multiplication Operator Overrides   *
    *                                       *
    *****************************************/

    
    // Overload the "*" operator for Number object
    Number operator*(const Number& other) {
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
    Number& operator*=(const Number& other){
        *this = *this * other;
        return *this; 
    }
    
    
    // Overload the "*" operator for double
    Number operator*(const double other){
        return *this * toNumber(other); 
    }

    // Overload the "*=" operator for double
    Number& operator*=(const double other){
        *this = *this * toNumber(other);
        return *this; 
    }

    /************************************
    *                                   *
    *   Division Operator Overrides     *
    *                                   *
    *************************************/

    // Overload the "/" operator for Number object
    Number operator/(const Number& other){
        if (this->mantissa == 0 || other.mantissa == 0){
            if (other.mantissa == 0) std::cerr << "\033[33m[WARN]\033[0m => Division by zero-ish Number. Returned 0e0." << endl << "Program attempted: " << this->printNumber() << " / " << other.printNumber() << endl;
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
    Number operator/(const double other){
        return *this / toNumber(other);
    }
    
    // Overload the "/=" operator for double
    Number& operator/=(const Number& other){
        *this = *this / other;
        return *this;
    }
    
    // Overload the "/=" operator for double
    Number& operator/=(const double other){
        *this = *this / toNumber(other);
        return *this;
    }

    /************************************
    *                                   *
    *   Comparative Operator Overrides  *
    *                                   *
    *************************************/

    // ----- == operator -----
    
    bool operator==(const Number& other){
        return (this->mantissa == other.mantissa) && (this->exponent == other.exponent);
    }

    bool operator==(const double other){
        return *this == toNumber(other);
    }

    // ----- != operator -----

    bool operator!=(const Number& other){
        return !(*this == other);
    }

    bool operator!=(const double other){
        return !(*this == toNumber(other));
    }

    // ----- < operator -----

    bool operator<(const Number& other){
        if (this->exponent == other.exponent){
            return this->mantissa < other.mantissa;
        }
        else {
            return this->exponent < other.exponent;
        }
    }

    bool operator<(const double other){
        return *this < toNumber(other);
    }

    // ----- <= operator -----

    bool operator<=(const Number& other){
        return (*this < other) || (*this == other);
    }

    bool operator<=(const double other){
        return (*this < toNumber(other)) || (*this == toNumber(other));
    }

    // ----- > operator -----

    bool operator>(const Number& other){
        if (this->exponent == other.exponent){
            return this->mantissa > other.mantissa;
        }
        else {
            return this->exponent > other.exponent;
        }
    }

    bool operator>(const double other){
        return *this > toNumber(other);
    }
    
    // ----- >= operator -----

    bool operator>=(const Number& other){
        return (*this > other) || (*this == other);
    }

    bool operator>=(const double other){
        return (*this > toNumber(other)) || (*this == toNumber(other));
    }

};

int main() {

    auto start = std::chrono::steady_clock::now();

    this_thread::sleep_for(chrono::milliseconds(2000));

    std::cout << "Starting Tests..." << std::endl;

    Number small(1, 5);   // 1e5
    Number large(1, 10);  // 1e10
    Number result(0, 0);

    bool comparator = false;

    int tests = 47;
    int completed = 0;

    // ----- Addition -----
    result = large + small;
    TEST_ASSERT(result.exponent == 10, "Test => large + small (expected exponent 10)", completed);
    TEST_ASSERT(result.mantissa > 1.00000f && result.mantissa < 1.00002f, "Test => large + small (mantissa check)", completed);

    result = small + small;
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 5, "Test => small + small (expected mantissa 2.0, exponent 5)", completed);

    // ----- += operator -----
    result = small;
    result += small;  // 1e5 += 1e5 => 2e5
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 5, "Test => small += small (expected mantissa 2.0, exponent 5)", completed);

    result = large;
    result += 100000;  // 1e10 += 1e5
    TEST_ASSERT(result.exponent == 10, "Test => large += 100000 (expected exponent 10)", completed);
    TEST_ASSERT(result.mantissa > 1.00000f && result.mantissa < 1.00002f, "Test => large += 100000 (mantissa check)", completed);

    // ----- Subtraction -----
    Number a(5, 6);
    Number b(2, 6);
    result = a - b;
    TEST_ASSERT(result.mantissa == 3.0f && result.exponent == 6, "Test => a - b (expected mantissa 3.0, exponent 6)", completed);

    result = b - a;
    TEST_ASSERT(result.mantissa == -3.0f && result.exponent == 6, "Test => b - a (expected mantissa -3.0, exponent 6)", completed);

    // ----- -= operator -----
    result = a;
    result -= b;  // 5e6 - 2e6 = 3e6
    TEST_ASSERT(result.mantissa == 3.0f && result.exponent == 6, "Test => a -= b (expected mantissa 3.0, exponent 6)", completed);

    result = small;
    result -= 0.5e5;  // 1e5 - 0.5e5 = 0.5e5
    TEST_ASSERT(result.mantissa == 5.0f && result.exponent == 4, "Test => small -= 0.5e5 (expected mantissa 5.0, exponent 4)", completed);

    // ----- Multiplication -----
    Number m1(2, 3);
    Number m2(3, 4);
    result = m1 * m2;
    TEST_ASSERT(result.mantissa == 6.0f && result.exponent == 7, "Test => m1 * m2 (expected mantissa 6.0, exponent 7)", completed);

    // ----- *= operator -----
    result = m1;
    result *= m2;
    TEST_ASSERT(result.mantissa == 6.0f && result.exponent == 7, "Test => m1 *= m2 (expected mantissa 6.0, exponent 7)", completed);

    result = m1;
    result *= 100;  // 2e3 * 1e2 = 2e5
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 5, "Test => m1 *= 100 (expected mantissa 2.0, exponent 5)", completed);

    // ----- Division -----
    Number d1(4, 6);
    Number d2(2, 5);
    result = d1 / d2;
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 1, "Test => d1 / d2 (expected mantissa 2.0, exponent 1)", completed);

    // ----- /= operator -----
    result = d1;
    result /= d2;  // 4e6 / 2e5 = 2e1
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 1, "Test => d1 /= d2 (expected mantissa 2.0, exponent 1)", completed);

    result = d1;
    result /= 10;  // 4e6 / 1e1 = 4e5
    TEST_ASSERT(result.mantissa == 4.0f && result.exponent == 5, "Test => d1 /= 10 (expected mantissa 4.0, exponent 5)", completed);

    // ----- Comparative Operators -----

    // ----- == operator -----
    comparator = small == small;
    TEST_ASSERT(comparator ==  true, "Test => small == small (expected true)", completed);

    comparator = small == large;
    TEST_ASSERT(comparator == false, "Test => small == large (expected false)", completed);

    comparator = small == 100000; // 1e5 == 1e5 / true
    TEST_ASSERT(comparator ==  true, "Test => small == 100000 (expected true)", completed);

    comparator = small == 5.0; // 1e5 == 5f / false
    TEST_ASSERT(comparator ==  false, "Test => small == 5.0 (expected false)", completed);

    // ----- != operator -----
    comparator = small != small;
    TEST_ASSERT(comparator ==  false, "Test => small != small (expected false)", completed);

    comparator = small != large;
    TEST_ASSERT(comparator == true, "Test => small != large (expected true)", completed);

    comparator = small != 100000; // 1e5 != 1e5 / false
    TEST_ASSERT(comparator ==  false, "Test => small != 100000 (expected false)", completed);

    comparator = small != 5.0; // 1e5 != 5f / true
    TEST_ASSERT(comparator ==  true, "Test => small != 5.0 (expected true)", completed);

    // ----- < operator -----
    comparator = small < small;
    TEST_ASSERT(comparator == false, "Test => small < small (expected false)", completed);

    comparator = small < large;
    TEST_ASSERT(comparator == true, "Test => small < large (expected true)", completed);

    comparator = small < 100000; // 1e5 < 1e5 / false
    TEST_ASSERT(comparator == false, "Test => small < 100000 (expected false)", completed);

    comparator = small < 5000000.0; // 1e5 < 5e6f / true
    TEST_ASSERT(comparator == true, "Test => small < 5000000.0 (expected true)", completed);

    // ----- <= operator -----
    comparator = small <= small;
    TEST_ASSERT(comparator == true, "Test => small <= small (expected true)", completed);

    comparator = small <= large;
    TEST_ASSERT(comparator == true, "Test => small <= large (expected true)", completed);

    comparator = small <= 100000; // 1e5 <= 1e5 / true
    TEST_ASSERT(comparator == true, "Test => small <= 100000 (expected true)", completed);

    comparator = small <= 50000.0; // 1e5 <= 5e4f / false
    TEST_ASSERT(comparator == false, "Test => small <= 50000.0 (expected false)", completed);

    // ----- > operator -----
    comparator = small > small;
    TEST_ASSERT(comparator == false, "Test => small > small (expected false)", completed);

    comparator = small > large;
    TEST_ASSERT(comparator == false, "Test => small > large (expected false)", completed);

    comparator = small > 1000; // 1e5 > 1e3 / true
    TEST_ASSERT(comparator == true, "Test => small > 1000 (expected true)", completed);

    comparator = small > 50000.0; // 1e5 < 5e4f / true
    TEST_ASSERT(comparator == true, "Test => small > 50000.0 (expected true)", completed);

    // ----- >= operator -----
    comparator = small >= small;
    TEST_ASSERT(comparator == true, "Test => small >= small (expected true)", completed);

    comparator = small >= large;
    TEST_ASSERT(comparator == false, "Test => small >= large (expected false)", completed);

    comparator = small >= 1000; // 1e5 >= 1e3 / true
    TEST_ASSERT(comparator == true, "Test => small >= 1000 (expected true)", completed);

    comparator = small >= 500000.0; // 1e5 >= 5e5f / false
    TEST_ASSERT(comparator == false, "Test => small >= 500000.0 (expected false)", completed);

    // ----- Zero edge cases -----
    Number zero(0, 0);
    result = zero + large;
    TEST_ASSERT(result.mantissa == 1.0f && result.exponent == 10, "Test => zero + large (expected mantissa 1.0, exponent 10)", completed);

    result = large * zero;
    TEST_ASSERT(result.mantissa == 0.0f && result.exponent == 0, "Test => large * zero (expected mantissa 0.0, exponent 0)", completed);

    result = zero - zero;
    TEST_ASSERT(result.mantissa == 0.0f && result.exponent == 0, "Test => zero - zero (expected mantissa 0.0, exponent 0)", completed);

    // ----- Output cases -----
    string output = small.printNumber(); // 1e5 / 100,000
    TEST_ASSERT(output == "100,000", "Test => small.printNumber() (expected '100,000')", completed);

    output = large.printNumber(); // 1e10 / "1e10"
    TEST_ASSERT(output == "1e10", "Test => large.printNumber() (expected '1e10')", completed);

    output = Number(1,-2).printNumber(); // 1e-2 / 0.01
    TEST_ASSERT(output == "0.01", "Test => Number(1,-2).printNumber() (expected '0.01')", completed);

    output = Number(1,-5).printNumber(); // 1e-5 / "1e-5"
    TEST_ASSERT(output == "1e-5", "Test => Number(1,-5).printNumber() (expected '1e-5')", completed);

    // Record end time
    auto end = std::chrono::steady_clock::now();

    // Calculate duration
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    // Output the duration
    cout << endl;
    cout << "---------------------------------" << endl;
    cout << "Elapsed time: " << microSecondsConverter(duration.count()) << std::endl;
    cout << "=================================" << endl;
    cout << completed << " / " << tests << " successful" << endl;
    cout << "---------------------------------" << endl;
    if (completed != tests) cout << tests-completed << " test(s) failed.";
    if (completed != tests) cout << "---------------------------------" << endl;
    return 0;
}