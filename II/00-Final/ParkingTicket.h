#ifndef PARKINGTICKETSIMULATOR_PARKINGTICKET_H
#define PARKINGTICKETSIMULATOR_PARKINGTICKET_H

#include "PoliceOfficer.h"
#include "CurrentTimeStamp.h"

/**
 * ParkingTicket encapsulates information about a ParkingTicket.
 * It stores information about a car that is being ticketed and the meter that
 * the car is parked near. It provides methods for determining the amount of a
 * fine that is to be given. Each time a ticket is created, a new ID is given
 * to the ticket, pulled from a file that increments the value to keep track of
 * the tickets issued. This provides some more realism for a ticket as each one
 * should have a unique identifier.
 * Methods are additionally provided to stream the information to an ostream
 * operator, allowing ticket information to be saved to file or displayed to the
 * screen.
 * Lastly, each time a ticket is created, the current date and time is recorded
 * and stored with the ticket.
 * Only getter method are provided as the information required by a ticket should
 * only be supplied during construction. If an "error" is made entering
 * information for a ticket, a new ticket should instead be created and the old
 * one should be voided but not deleted to maintain proper record keeping.
 */
class ParkingTicket {
public:
    static constexpr double FINE_FIRST_HOUR = 25.00;
    static constexpr double FINE_ADDITIONAL = 10.00;
private:
    unsigned int ticketId;
    int timeInfraction;
    ParkedCar car;
    ParkingMeter meter;
    PoliceOfficer officer;
    CurrentTimeStamp * timeStamp = nullptr;
public:
    class NoViolation : public std::exception {
    public:
        NoViolation() = default;
    };
    ParkingTicket() = delete;
    ParkingTicket(const ParkedCar &car, const ParkingMeter &meter,
                  const PoliceOfficer &officer);
    ~ParkingTicket();
    const ParkedCar &getCar() const;
    const ParkingMeter &getMeter() const;
    const PoliceOfficer &getOfficer() const;
    double getFine() const;
    CurrentTimeStamp * getTimeStamp() const;
    unsigned int getTicketId() const;
    void overrideTicketId(long idNumber);
    void printTicket(std::ostream &stream);
private:
    void setTicketId();
    unsigned int getTicketNumberFromFile();
    unsigned int readIdFromFile(std::ifstream &stream);
    void setNextTicketIdInFile(unsigned int currentId,
                               const std::string &fileLoc);
    void writeNewIdToFile(unsigned int id, std::ofstream &stream);
};


#endif //PARKINGTICKETSIMULATOR_PARKINGTICKET_H
