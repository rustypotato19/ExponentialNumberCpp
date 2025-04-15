#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>
#include <cassert>

using namespace std;

#define TEST_ASSERT(condition, message, completed) \
    do { \
        if (!(condition)) { \
            std::cerr << "[FAIL] " << message << " (Line " << __LINE__ << ")\n"; \
        } else { \
            std::cout << "[PASS] " << message << "\n"; \
            ++(completed); \
        } \
    } while(0)

string addCommas(string numStr) {
    int len = numStr.length();
    int insertPosition = len - 3;

    while (insertPosition > 0) {
        numStr.insert(insertPosition, ",");
        insertPosition -= 3;
    }

    return numStr;
}

string microSecondsConverter(const int microseconds) {
    ostringstream time;

    if (microseconds / 1000 < 1) {
        return to_string(microseconds) + " microsecond(s)";
    }
    else if (microseconds / 1000000 < 1)
    {
        float miliseconds = microseconds / 1000;
        time << fixed << setprecision(2) << miliseconds;
        return time.str() + " milisecond(s)";
    }
    else {
        float seconds = microseconds / 1000000;
        time << fixed << setprecision(2) << seconds;
        return time.str() + " second(s)";
    }
    
}