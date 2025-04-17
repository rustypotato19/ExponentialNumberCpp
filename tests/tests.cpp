// tests/tests.cpp

#include "../include/utils.h"
#include "../include/tests.h"
#include "../include/main.h"
#include "../include/number.h"

void runTests(){
    auto start = std::chrono::steady_clock::now();

    //this_thread::sleep_for(chrono::milliseconds(2000));

    std::cout << "Starting Tests..." << std::endl;
    this_thread::sleep_for(chrono::milliseconds(500));

    Number small(1, 5);   // 1e5
    Number large(1, 10);  // 1e10
    Number result(0, 0);

    bool comparator = false;

    int tests = 0;
    int completed = 0;

    // ----- Addition -----
    result = large + small;
    TEST_ASSERT(result.exponent == 10, "Test => large + small (expected exponent 10)", completed, tests);
    TEST_ASSERT(result.mantissa > 1.00000f && result.mantissa < 1.00002f, "Test => large + small (mantissa check)", completed, tests);

    result = small + small;
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 5, "Test => small + small (expected mantissa 2.0, exponent 5)", completed, tests);

    // ----- += operator -----
    result = small;
    result += small;  // 1e5 += 1e5 => 2e5
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 5, "Test => small += small (expected mantissa 2.0, exponent 5)", completed, tests);

    result = large;
    result += 100000;  // 1e10 += 1e5
    TEST_ASSERT(result.exponent == 10, "Test => large += 100000 (expected exponent 10)", completed, tests);
    TEST_ASSERT(result.mantissa > 1.00000f && result.mantissa < 1.00002f, "Test => large += 100000 (mantissa check)", completed, tests);

    // ----- Subtraction -----
    Number a(5, 6);
    Number b(2, 6);
    result = a - b;
    TEST_ASSERT(result.mantissa == 3.0f && result.exponent == 6, "Test => a - b (expected mantissa 3.0, exponent 6)", completed, tests);

    result = b - a;
    TEST_ASSERT(result.mantissa == -3.0f && result.exponent == 6, "Test => b - a (expected mantissa -3.0, exponent 6)", completed, tests);

    // ----- -= operator -----
    result = a;
    result -= b;  // 5e6 - 2e6 = 3e6
    TEST_ASSERT(result.mantissa == 3.0f && result.exponent == 6, "Test => a -= b (expected mantissa 3.0, exponent 6)", completed, tests);

    result = small;
    result -= 0.5e5;  // 1e5 - 0.5e5 = 0.5e5
    TEST_ASSERT(result.mantissa == 5.0f && result.exponent == 4, "Test => small -= 0.5e5 (expected mantissa 5.0, exponent 4)", completed, tests);

    // ----- Multiplication -----
    Number m1(2, 3);
    Number m2(3, 4);
    result = m1 * m2;
    TEST_ASSERT(result.mantissa == 6.0f && result.exponent == 7, "Test => m1 * m2 (expected mantissa 6.0, exponent 7)", completed, tests);

    // ----- *= operator -----
    result = m1;
    result *= m2;
    TEST_ASSERT(result.mantissa == 6.0f && result.exponent == 7, "Test => m1 *= m2 (expected mantissa 6.0, exponent 7)", completed, tests);

    result = m1;
    result *= 100;  // 2e3 * 1e2 = 2e5
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 5, "Test => m1 *= 100 (expected mantissa 2.0, exponent 5)", completed, tests);

    // ----- Division -----
    Number d1(4, 6);
    Number d2(2, 5);
    result = d1 / d2;
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 1, "Test => d1 / d2 (expected mantissa 2.0, exponent 1)", completed, tests);

    // ----- /= operator -----
    result = d1;
    result /= d2;  // 4e6 / 2e5 = 2e1
    TEST_ASSERT(result.mantissa == 2.0f && result.exponent == 1, "Test => d1 /= d2 (expected mantissa 2.0, exponent 1)", completed, tests);

    result = d1;
    result /= 10;  // 4e6 / 1e1 = 4e5
    TEST_ASSERT(result.mantissa == 4.0f && result.exponent == 5, "Test => d1 /= 10 (expected mantissa 4.0, exponent 5)", completed, tests);

    // ----- Comparative Operators -----

    // ----- == operator -----
    comparator = small == small;
    TEST_ASSERT(comparator ==  true, "Test => small == small (expected true)", completed, tests);

    comparator = small == large;
    TEST_ASSERT(comparator == false, "Test => small == large (expected false)", completed, tests);

    comparator = small == 100000; // 1e5 == 1e5 / true
    TEST_ASSERT(comparator ==  true, "Test => small == 100000 (expected true)", completed, tests);

    comparator = small == 5.0; // 1e5 == 5f / false
    TEST_ASSERT(comparator ==  false, "Test => small == 5.0 (expected false)", completed, tests);

    // ----- != operator -----
    comparator = small != small;
    TEST_ASSERT(comparator ==  false, "Test => small != small (expected false)", completed, tests);

    comparator = small != large;
    TEST_ASSERT(comparator == true, "Test => small != large (expected true)", completed, tests);

    comparator = small != 100000; // 1e5 != 1e5 / false
    TEST_ASSERT(comparator ==  false, "Test => small != 100000 (expected false)", completed, tests);

    comparator = small != 5.0; // 1e5 != 5f / true
    TEST_ASSERT(comparator ==  true, "Test => small != 5.0 (expected true)", completed, tests);

    // ----- < operator -----
    comparator = small < small;
    TEST_ASSERT(comparator == false, "Test => small < small (expected false)", completed, tests);

    comparator = small < large;
    TEST_ASSERT(comparator == true, "Test => small < large (expected true)", completed, tests);

    comparator = small < 100000; // 1e5 < 1e5 / false
    TEST_ASSERT(comparator == false, "Test => small < 100000 (expected false)", completed, tests);

    comparator = small < 5000000.0; // 1e5 < 5e6f / true
    TEST_ASSERT(comparator == true, "Test => small < 5000000.0 (expected true)", completed, tests);

    // ----- <= operator -----
    comparator = small <= small;
    TEST_ASSERT(comparator == true, "Test => small <= small (expected true)", completed, tests);

    comparator = small <= large;
    TEST_ASSERT(comparator == true, "Test => small <= large (expected true)", completed, tests);

    comparator = small <= 100000; // 1e5 <= 1e5 / true
    TEST_ASSERT(comparator == true, "Test => small <= 100000 (expected true)", completed, tests);

    comparator = small <= 50000.0; // 1e5 <= 5e4f / false
    TEST_ASSERT(comparator == false, "Test => small <= 50000.0 (expected false)", completed, tests);

    // ----- > operator -----
    comparator = small > small;
    TEST_ASSERT(comparator == false, "Test => small > small (expected false)", completed, tests);

    comparator = small > large;
    TEST_ASSERT(comparator == false, "Test => small > large (expected false)", completed, tests);

    comparator = small > 1000; // 1e5 > 1e3 / true
    TEST_ASSERT(comparator == true, "Test => small > 1000 (expected true)", completed, tests);

    comparator = small > 50000.0; // 1e5 < 5e4f / true
    TEST_ASSERT(comparator == true, "Test => small > 50000.0 (expected true)", completed, tests);

    // ----- >= operator -----
    comparator = small >= small;
    TEST_ASSERT(comparator == true, "Test => small >= small (expected true)", completed, tests);

    comparator = small >= large;
    TEST_ASSERT(comparator == false, "Test => small >= large (expected false)", completed, tests);

    comparator = small >= 1000; // 1e5 >= 1e3 / true
    TEST_ASSERT(comparator == true, "Test => small >= 1000 (expected true)", completed, tests);

    comparator = small >= 500000.0; // 1e5 >= 5e5f / false
    TEST_ASSERT(comparator == false, "Test => small >= 500000.0 (expected false)", completed, tests);

    // ----- Zero edge cases -----
    Number zero(0, 0);
    result = zero + large;
    TEST_ASSERT(result.mantissa == 1.0f && result.exponent == 10, "Test => zero + large (expected mantissa 1.0, exponent 10)", completed, tests);

    result = large * zero;
    TEST_ASSERT(result.mantissa == 0.0f && result.exponent == 0, "Test => large * zero (expected mantissa 0.0, exponent 0)", completed, tests);

    result = zero - zero;
    TEST_ASSERT(result.mantissa == 0.0f && result.exponent == 0, "Test => zero - zero (expected mantissa 0.0, exponent 0)", completed, tests);

    // ----- Output cases -----
    string output = small.printNumber(); // 1e5 / "100,000"
    TEST_ASSERT(output == "100,000", "Test => small.printNumber() (expected '100,000')", completed, tests);

    output = large.printNumber(); // 1e10 / "1e10"
    TEST_ASSERT(output == "1e10", "Test => large.printNumber() (expected '1e10')", completed, tests);

    output = Number(1,-2).printNumber(); // 1e-2 / 0.01
    TEST_ASSERT(output == "0.01", "Test => Number(1,-2).printNumber() (expected '0.01')", completed, tests);

    output = Number(1,-5).printNumber(); // 1e-5 / "1e-5"
    TEST_ASSERT(output == "1e-5", "Test => Number(1,-5).printNumber() (expected '1e-5')", completed, tests);

    output = Number(1,4).printNumber(); // 1e4 / "10,000"
    TEST_ASSERT(output == "10,000", "Test => Number(1,4).printNumber() (expected '10,000')", completed, tests);

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
}