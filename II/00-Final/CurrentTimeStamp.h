#ifndef PARKINGTICKETSIMULATOR_CURRENTTIMESTAMP_H
#define PARKINGTICKETSIMULATOR_CURRENTTIMESTAMP_H

#include <chrono>
#include <ctime>
#include <string>

/**
 * CurrentTimeStamp encapsulates a ctime struct with the date and time of the
 * (local) system time at the time of instantiation. It provides methods for
 * getting both the date and time of the time stamp created. This class is used
 * for notating the time and date a ParkingTicket is issued.
 */
class CurrentTimeStamp {
private:
    std::tm * tm_now = nullptr;
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
public:
    CurrentTimeStamp();
    std::string getDateString();
    std::string getTimeString();
    ~CurrentTimeStamp() = default;
private:
    void getTimeNow();
};

#endif //PARKINGTICKETSIMULATOR_CURRENTTIMESTAMP_H
