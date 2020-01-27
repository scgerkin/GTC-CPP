#include "PoliceOfficer.h"
#include "ParkingTicket.h"

/**
 * Default constructor requires information about a police officer to construct.
 * @param name The name of the officer.
 * @param badgeNumber The badge number of the officer.
 */
PoliceOfficer::PoliceOfficer(const std::string &name,
                             const std::string &badgeNumber)
        : name(name), badgeNumber(badgeNumber) {}

/**
 * Determines if a car has been parked longer than the time purchased for the
 * meter.
 * @param car The car we are inspecting.
 * @param meter The meter the car is parked next to.
 * @return TRUE if a car is parked beyond the amount of time purchased.
 */
bool PoliceOfficer::carTimeExpired(const ParkedCar &car,
                                   const ParkingMeter &meter) {
    return car.getMinutesParked() > meter.getMinutesPurchased();
}

/**
 * Creates a new ParkingTicket object and returns a pointer to the object using
 * the information provided.
 * @param car The car we are to ticket.
 * @param meter The meter the car is parked next to.
 * @return A pointer to a new ParkingTicket object.
 */
ParkingTicket * PoliceOfficer::issueTicket(ParkedCar * car,
                                           ParkingMeter * meter) {
    return new ParkingTicket(*car, *meter, *this);
}

/**
 * Getter for name.
 */
const std::string &PoliceOfficer::getName() const {
    return name;
}

/**
 * Setter for name.
 */
void PoliceOfficer::setName(const std::string &name) {
    PoliceOfficer::name = name;
}

/**
 * Getter for badgeNumber.
 */
const std::string &PoliceOfficer::getBadgeNumber() const {
    return badgeNumber;
}

/**
 * Setter for badgeNumber.
 */
void PoliceOfficer::setBadgeNumber(const std::string &badgeNumber) {
    PoliceOfficer::badgeNumber = badgeNumber;
}
