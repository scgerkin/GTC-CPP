#ifndef PARKINGTICKETSIMULATOR_SIMULATOR_H
#define PARKINGTICKETSIMULATOR_SIMULATOR_H

#include <stdexcept>
#include <string>
#include "PoliceOfficer.h"

/**
 * Simulation class for demonstrating program functionality.
 * It displays information to the user and gets input for issuing tickets.
 * As the user moves from car to car, a new ParkedCar and ParkingMeter is
 * instantiated with a random integer value for the amount of time parked and
 * the amount of time purchased for the meter. The user can then inspect both
 * the car and the meter to determine if a ticket should be written. The process
 * loops until the user enters input indicating the desire to quit, at which
 * time an exception is thrown to signal the end of the simulation.
 * Additionally, each time a ticket is written by the user, it is appended to a
 * file that contains all the tickets written across any runs of the program.
 */
class Simulator {
private:
    static const std::string QUIT; // string to signal user wants to exit.
    static const std::string FILE_NAME; // the file we use for the ticket book.
    static constexpr int MAX_MINUTES = 6001; // the max minutes we use for time.
    PoliceOfficer * officer = nullptr; // the officer object we use for simulation.
    ParkedCar * car = nullptr; // created dynamically through program run.
    ParkingMeter * meter = nullptr; // created dynamically through program run.
public:
    /**
     * QuitException is for signaling the user's desire to exit the simulation.
     */
    class QuitException : public std::exception {
        public:
            QuitException() = default;
        };
public:
    /*Constructors and destructors*/
    Simulator() = default;
    ~Simulator();
    void start();
private:
    void displayWelcomeMsg();
    void constructOfficer();
    void patrol();
    void moveAlong();
    void inspectCar();
    void recordCarInformation();
    void inspectMeter();
    void writeTicket();
    void successfulTicket(ParkingTicket * ticket);
    void unsuccessfulTicketAttempt();
    int getRandomInt();
    std::string getStringInput(const std::string &inputMsg);
    int getMenuSelection(int maxMenu);
    int getIntegerInput(const std::string &inputType);
    int getIntegerInput();
};


#endif //PARKINGTICKETSIMULATOR_SIMULATOR_H
