#ifndef PARKINGTICKETSIMULATOR_PARKEDCAR_H
#define PARKINGTICKETSIMULATOR_PARKEDCAR_H

#include <string>

/**
 * ParkedCar represents a car parked on the street.
 * It stores information about the car and provides getters and setters for this
 * information. It additionally stores the amount of time the car has been
 * parked.
 */
class ParkedCar {
private:
    int minutesParked;
    std::string make;
    std::string model;
    std::string color;
    std::string licenseNumber;
public:
    ParkedCar() = delete;
    explicit ParkedCar(int minutesParked);
    ParkedCar(int minutesParked, const std::string &make,
              const std::string &model, const std::string &color,
              const std::string &licenseNumber);
    ~ParkedCar() = default;
    bool incompleteInformation() const;
    /*Getters and setters*/
    int getMinutesParked() const;
    void setMinutesParked(int minutesParked);
    const std::string &getMake() const;
    void setMake(const std::string &make);
    const std::string &getModel() const;
    void setModel(const std::string &model);
    const std::string &getColor() const;
    void setColor(const std::string &color);
    const std::string &getLicenseNumber() const;
    void setLicenseNumber(const std::string &licenseNumber);
};

#endif //PARKINGTICKETSIMULATOR_PARKEDCAR_H
