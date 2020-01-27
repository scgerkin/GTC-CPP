#include "ParkingTicket.h"
#include "IOException.h"
#include <fstream>
#include <iostream>
#include <iomanip>

/**
 * Default constructor requires information about a car, the information from a
 * parking meter, and the information for the issuing officer in order to be
 * instantiated.
 * @param car The car that is in violation.
 * @param meter The parking meter the car is parked near.
 * @param officer The officer issuing the ticket.
 */
ParkingTicket::ParkingTicket(const ParkedCar &car, const ParkingMeter &meter,
                             const PoliceOfficer &officer)
        : car(car), meter(meter), officer(officer) {
    timeInfraction = car.getMinutesParked() - meter.getMinutesPurchased();
    if (timeInfraction <= 0) {
        throw NoViolation();
    }
    timeStamp = new CurrentTimeStamp;
    setTicketId();
}

/**
 * Frees memory we use for storing the time stamp.
 */
ParkingTicket::~ParkingTicket() {
    delete timeStamp;
}

/**
 * Getter for car.
 */
const ParkedCar &ParkingTicket::getCar() const {
    return car;
}

/**
 * Getter for meter.
 */
const ParkingMeter &ParkingTicket::getMeter() const {
    return meter;
}

/**
 * Getter for officer.
 */
const PoliceOfficer &ParkingTicket::getOfficer() const {
    return officer;
}

/**
 * Calculates and returns the amount of fine for the ticket.
 * @return The amount of the fine.
 */
double ParkingTicket::getFine() const {
    int temp = timeInfraction;
    double fine = 0;

    fine += FINE_FIRST_HOUR;
    temp -= 60;

    while (temp > 0) {
        fine += FINE_ADDITIONAL;
        temp -= 60;
    }

    return fine;
}

/**
 * Getter for the ticket timeStamp.
 */
CurrentTimeStamp * ParkingTicket::getTimeStamp() const {
    return timeStamp;
}

/**
 * Getter for the ticketId.
 */
unsigned int ParkingTicket::getTicketId() const {
    return ticketId;
}

/**
 * Method to override the ticket number that was set during creation.
 * Should ideally only be used if there was an issue getting the ticketId from
 * file.
 * @param idNumber The ID number we wish to set for this particular ticket.
 */
void ParkingTicket::overrideTicketId(long idNumber) {
    ticketId = idNumber;
}

/**
 * Streams the ticket to an ostream object (i.e. cout or file output).
 * @param stream The stream we are to put the ticket into.
 */
void ParkingTicket::printTicket(std::ostream &stream) {
    stream << "___________\n"
           << "Ticket number: " << getTicketId() << "\n"
           << "Date: " << timeStamp->getDateString() << " Time: "
           << timeStamp->getTimeString() << "\n"
           << "CAR DETAILS\n"
           << "Make: " << car.getMake() << " Model: " << car.getModel() << "\n"
           << "Color: " << car.getColor() << " License: " << car.getLicenseNumber() << "\n"
           << "FINE DETAILS\n"
           << "Violation: " << car.getMinutesParked() - meter.getMinutesPurchased() << " minutes.\n"
           << "Fine amount: $" << std::fixed << std::setprecision(2) << getFine() << "\n"
           << "Issuing officer: " << officer.getName() << " Badge #: " << officer.getBadgeNumber() << "\n";
}

/**
 * Sets the ticketId number we use for this ticket. Attempts to set it from a
 * file that is incremented each time a ParkingTicket object is created, but
 * will set the ticketId to -1 as a flag if there is a problem processing the
 * file.
 */
void ParkingTicket::setTicketId() {
    try {
        ticketId = getTicketNumberFromFile();
    }
    catch (const IOException &ex) {
        overrideTicketId(-1);
    }
}

/**
 * Gets the current ticketId from our file that maintains this information and
 * then updates the file with the new number to use at the next call.
 * @return The number we receive from the file.
 */
unsigned int ParkingTicket::getTicketNumberFromFile() {
    std::ifstream inFile;
    std::string fileLoc = "ticket-sequence.dat";

    try {
        inFile.open(fileLoc, std::ios_base::in);
        long idNumber = readIdFromFile(inFile);
        inFile.close();
        setNextTicketIdInFile(idNumber, fileLoc);
        return idNumber;
    }
    catch (const std::exception &ex) {
        throw IOException(__FUNCTION__);
    }
}

/**
 * Reads the next ticketId from file.
 * @param stream The stream for the file we are reading from.
 * @return The next ticketId number.
 */
unsigned int ParkingTicket::readIdFromFile(std::ifstream &stream) {
    try {
        unsigned int id;
        stream >> id;
        return id;
    }
    catch (const std::exception &ex) {
        throw IOException(__FUNCTION__);
    }
}

/**
 * Saves the next ID number to the file used for maintaining ticket IDs.
 * @param currentId The ID we used for the current ticket.
 * @param fileLoc The file name where information is to be stored.
 */
void ParkingTicket::setNextTicketIdInFile(unsigned int currentId,
                                          const std::string &fileLoc) {
    currentId++;
    std::ofstream outFile;

    try {
        outFile.open(fileLoc, std::ios::out);
        writeNewIdToFile(currentId, outFile);
        outFile.close();
    }
    catch (const std::exception &ex) {
        throw IOException(__FUNCTION__);
    }
}

/**
 * Writes a new ID number to file.
 * @param id The ID number we wish to write.
 * @param stream The stream for the file we are using.
 */
void ParkingTicket::writeNewIdToFile(unsigned int id, std::ofstream &stream) {
    try {
        stream << id;
    }
    catch (const std::exception &ex) {
        throw IOException(__FUNCTION__);
    }
}
