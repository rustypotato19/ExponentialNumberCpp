#include "../include/utils.h"
#include <sstream>
#include <iomanip>
#include <string>

std::string addCommas(std::string numStr) {
    int len = numStr.length();
    int insertPosition = len - 3;

    while (insertPosition > 0) {
        numStr.insert(insertPosition, ",");
        insertPosition -= 3;
    }

    return numStr;
}

std::string microSecondsConverter(const long long int microseconds) {
    std::ostringstream time;

    if (microseconds / 1000 < 1) {
        return std::to_string(microseconds) + " microsecond(s)";
    } else if (microseconds / 1000000 < 1) {
        float miliseconds = microseconds / 1000.0f;
        time << std::fixed << std::setprecision(2) << miliseconds;
        return time.str() + " milisecond(s)";
    } else {
        float seconds = microseconds / 1000000.0f;
        time << std::fixed << std::setprecision(2) << seconds;
        return time.str() + " second(s)";
    }
}
