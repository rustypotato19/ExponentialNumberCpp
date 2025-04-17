#ifndef TESTS_H
#define TESTS_H

#include <chrono>
#include <thread>
#include <iostream>  // also good to have for std::cerr / std::cout

using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

void runTests();

#define TEST_ASSERT(condition, message, completed, tests)                           \
    sleep_for(milliseconds(50));                                                    \
    ++(tests);                                                                      \
    do {                                                                            \
        if (!(condition)) {                                                         \
            std::cerr << "[FAIL] " << message << " (Line " << __LINE__ << ")\n";    \
            sleep_for(milliseconds(500));                                           \
        } else {                                                                    \
            std::cout << "[PASS] " << message << "\n";                              \
            ++(completed);                                                          \
        }                                                                           \
    } while(0)

#endif // TESTS_H
