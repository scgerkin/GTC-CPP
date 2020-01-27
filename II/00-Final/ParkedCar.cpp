#include <stdexcept>
#include "ParkedCar.h"

/**
 * Default constructor.
 * Requires the amount of time that a car has been parked.
 * @param minutesParked The amount of time a car has been parked.
 * @throws std::runtime_error if minutes parked is less than 0.
 */
ParkedCar::ParkedCar(int minutesParked) {
    setMinutesParked(minutesParked);
}

/**
 * Full argument constructor.
 * Requires all fields of ParkedCar to be set. Used mainly for debugging user
 * interface, allowing for bypassing entry of car information during program
 * run.
 * @param minutesParked The amount of time a car has been parked.
 * @param make The make of the car (i.e. Chevy).
 * @param model The model of the car (i.e. Sonic).
 * @param color The color of the car (i.e. Grey).
 * @param licenseNumber The license plate number of the car.
 * @throws std::runtime_error if minutes parked is less than 0.
 */
ParkedCar::ParkedCar(int minutesParked, const std::string &make,
                     const std::string &model, const std::string &color,
                     const std::string &licenseNumber)
        : make(make), model(model), color(color),
          licenseNumber(licenseNumber) {
    setMinutesParked(minutesParked);
}

/**
 * For determining if all required information for filing a report about a car
 * has been filled. Checks for make, model, color, and license number.
 * @return If any one field is an empty string, this will return TRUE.
 */
bool ParkedCar::incompleteInformation() const {
    return make.empty() || model.empty() || color.empty() ||
           licenseNumber.empty();
}

/**
 * Getter for minutesParked.
 */
int ParkedCar::getMinutesParked() const {
    return minutesParked;
}

/**
 * Setter for minutesParked.
 * @throws std::runtime_error if minutes parked is less than 0.
 */
void ParkedCar::setMinutesParked(int minutesParked) {
    if (minutesParked < 0) {
        throw std::runtime_error("Minutes cannot be less than 0.");
    }
    ParkedCar::minutesParked = minutesParked;
}

/**
 * Getter for make.
 */
const std::string &ParkedCar::getMake() const {
    return make;
}

/**
 * Setter for make.
 */
void ParkedCar::setMake(const std::string &make) {
    ParkedCar::make = make;
}

/**
 * Getter for model.
 */
const std::string &ParkedCar::getModel() const {
    return model;
}

/**
 * Setter for model.
 * @param model
 */
void ParkedCar::setModel(const std::string &model) {
    ParkedCar::model = model;
}

/**
 * Getter for color.
 */
const std::string &ParkedCar::getColor() const {
    return color;
}

/**
 * Setter for color.
 * @param color
 */
void ParkedCar::setColor(const std::string &color) {
    ParkedCar::color = color;
}

/**
 * Getter for licenseNumber.
 */
const std::string &ParkedCar::getLicenseNumber() const {
    return licenseNumber;
}

/**
 * Setter for licenseNumber.
 */
void ParkedCar::setLicenseNumber(const std::string &licenseNumber) {
    ParkedCar::licenseNumber = licenseNumber;
}
