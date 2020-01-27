#include <stdexcept>
#include "ParkingMeter.h"

/**
 * Default constructor.
 * Initializes the amount of time purchased for the meter.
 * Minutes purchased must be an integer value greater than 0.
 * @param minutesPurchased The amount of minutes purchased.
 * @throws std::runtime_error if minutes purchased is less than 0.
 */
ParkingMeter::ParkingMeter(int minutesPurchased)
        : minutesPurchased(minutesPurchased) {
    if (minutesPurchased < 0) {
        throw std::runtime_error("Minutes cannot be less than 0.");
    }
}

/**
 * Getter for number of minutes purchased at this meter.
 */
int ParkingMeter::getMinutesPurchased() const {
    return minutesPurchased;
}

