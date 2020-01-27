#ifndef PARKINGTICKETSIMULATOR_PARKINGMETER_H
#define PARKINGTICKETSIMULATOR_PARKINGMETER_H

/**
 * ParkingMeter represents a parking meter that would be on a street.
 * Minutes for parking are purchased at the parking meter for allowing cars to
 * park on the street. This is essentially a wrapper class for an integer value.
 * It can only be instantiated with an existing value for the minutes parked.
 */
class ParkingMeter {
private:
    int minutesPurchased;
public:
    ParkingMeter() = delete;

    ParkingMeter(int minutesPurchased);

    int getMinutesPurchased() const;
};

#endif //PARKINGTICKETSIMULATOR_PARKINGMETER_H
