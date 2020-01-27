#ifndef PARKINGTICKETSIMULATOR_POLICEOFFICER_H
#define PARKINGTICKETSIMULATOR_POLICEOFFICER_H

class ParkingTicket; // forward declaration of ParkingTicket

#include "ParkedCar.h"
#include "ParkingMeter.h"
#include <string>

/**
 * PoliceOfficer encapsulates information about an officer issuing parking
 * tickets.
 * The class is responsible for knowing the name of the officer, their badge
 * number, and creating ParkingTicket objects.
 */
class PoliceOfficer {
private:
    std::string name;
    std::string badgeNumber;
public:
    /*Constructors/destructors*/
    PoliceOfficer() = delete;
    PoliceOfficer(const std::string &name, const std::string &badgeNumber);
    ~PoliceOfficer() = default;

    /*Class functionality*/
    ParkingTicket * issueTicket(ParkedCar * car, ParkingMeter * meter);
    bool carTimeExpired(const ParkedCar &car, const ParkingMeter &meter);

    /*Getters and setters*/
    const std::string &getName() const;
    void setName(const std::string &name);
    const std::string &getBadgeNumber() const;
    void setBadgeNumber(const std::string &badgeNumber);
};

#endif //PARKINGTICKETSIMULATOR_POLICEOFFICER_H
