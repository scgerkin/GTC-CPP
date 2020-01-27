#include "CurrentTimeStamp.h"

#include <chrono>
#include <ctime>

/**
 * Constructor gets the current local system time and stores it in the tm_now
 * struct. The individual values from the struct are then stored in their
 * respective member variables.
 */
CurrentTimeStamp::CurrentTimeStamp() {
    getTimeNow();
    year = tm_now->tm_year + 1900;
    month = tm_now->tm_mon + 1;
    day = tm_now->tm_mday;
    hour = tm_now->tm_hour;
    minute = tm_now->tm_min;
    second = tm_now->tm_sec;
}

/**
 * Gets the current local system time and puts it in the struct that holds this
 * information.
 */
void CurrentTimeStamp::getTimeNow() {
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(now);
    tm_now = std::localtime(&time);
}

/**
 * Gets a formatted string of the CurrentTimeStamp date in the form MM/DD/YYYY.
 * @return A string containing the date in form MM/DD/YYYY.
 */
std::string CurrentTimeStamp::getDateString() {
    using std::to_string;
    return to_string(month)
            + "/" + to_string(day) + "/" + to_string(year);
}

/**
 * Gets a formatted string of the CurrentTimeStamp time in the form HH:MM:SS.
 * @return A string containing the time in form HH:MM:SS.
 */
std::string CurrentTimeStamp::getTimeString() {
    using std::to_string;
    return to_string(hour) +
            ":" + to_string(minute) + ":"
            + ((second < 10)? "0" : "") + to_string(second);
}
