#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "Simulator.h"
#include "StringTools.h"
#include "ParkingTicket.h"

#define DEBUG 0 // set 1 to skip some input and always allow ticketing

const std::string Simulator::QUIT = "quit";
const std::string Simulator::FILE_NAME = "ticket-book.txt";

/**
 * Destructor frees the memory we use for the objects in the simulation if not
 * already freed.
 */
Simulator::~Simulator() {
    delete officer;
    delete car;
    delete meter;
}

/**
 * For starting the simulation.
 * Initializes the seed we will use for random values when creating ParkedCar
 * and ParkingMeter objects.
 */
void Simulator::start() {
    srand(time(0));
    displayWelcomeMsg();
    constructOfficer();
    while (true) {
        patrol();
    }
}

/**
 * Displays information about how the program will work to the user.
 */
void Simulator::displayWelcomeMsg() {
    using std::cout;
    cout << "Welcome to the Parking Ticket Simulator.\n"
         << "This program will simulate a police officer issuing parking tickets.\n"
         << "Any tickets you issue will be saved to your ticket book.\n"
         << "You can view your ticket book by opening the file named:\n"
         << FILE_NAME << "\n\n";
}

/**
 * Builds the PoliceOfficer we are going to use for the simulation from user
 * input.
 */
void Simulator::constructOfficer() {
#if DEBUG
    officer = new PoliceOfficer("test", "test");
#else
    std::cout << "Let's start by creating your Officer profile.\n";
    std::string name = getStringInput("your name");
    std::string badge = getStringInput("your badge number");
    officer = new PoliceOfficer(name, badge);
#endif
}

/**
 * Method that is called infinitely (until quit) that allows us to interact
 * with ParkedCar and ParkingMeter objects. It instantiates a new ParkedCar
 * and ParkingMeter each time the method is called, allowing the user to have
 * different values for moving through the street. The objects are deleted once
 * after all methods are done and the stack unwinds.
 */
void Simulator::patrol() {
#if DEBUG
    car = new ParkedCar(200, "test", "test", "test", "test");
    meter = new ParkingMeter(100);
#else
    car = new ParkedCar(getRandomInt());
    meter = new ParkingMeter(getRandomInt());
#endif
    std::cout << "You come across a parked car.\n"
              << "What do you want to do?\n"
              << "1. Inspect the car.\n"
              << "2. Inspect the parking meter.\n"
              << "3. Write a ticket for the car.\n"
              << "4. Move along... (ignore this car).\n";

    int selection = getMenuSelection(4);

    switch (selection) {
        case 1:
            inspectCar();
            break;
        case 2:
            inspectMeter();
            break;
        case 3:
            writeTicket();
            break;
        case 4:
            moveAlong();
            break;
    }

    delete car;
    delete meter;
}

/**
 * Inspects our ParkedCar object to determine how long it has been parked and
 * asks what we want to do with this information.
 */
void Simulator::inspectCar() {
    std::cout << "The car has been parked for " << car->getMinutesParked()
              << " minutes\n"
              << "You have " << (car->incompleteInformation() ? "not " : "")
              << "recorded this car's information.\n\n"
              << "What do you want to do?\n"
              << "1. Record or change the car information\n"
              << "2. Inspect the parking meter.\n"
              << "3. Write a ticket.\n"
              << "4. Move along... (ignore this car).\n";

    int selection = getMenuSelection(4);

    switch (selection) {
        case 1:
            recordCarInformation();
            break;
        case 2:
            inspectMeter();
            break;
        case 3:
            writeTicket();
            break;
        case 4:
            moveAlong();
            break;
    }
}

/**
 * Records the information about a car and asks how we want to proceed.
 */
void Simulator::recordCarInformation() {
    car->setMake(getStringInput("car make"));
    car->setModel(getStringInput("car model"));
    car->setColor(getStringInput("car color"));
    car->setLicenseNumber(getStringInput("license plate"));

    std::cout << "You notate this information in the ticket book...\n"
              << "What do you want to do?\n"
              << "1. Inspect the parking meter.\n"
              << "2. Write a ticket.\n"
              << "3. Move along... (ignore this car).\n";

    int selection = getMenuSelection(3);

    switch (selection) {
        case 1:
            inspectMeter();
            break;
        case 2:
            writeTicket();
            break;
        case 3:
            moveAlong();
            break;
    }
}

/**
 * Inspects a ParkingMeter object to see how much time has been purchased for
 * this meter.
 */
void Simulator::inspectMeter() {
    std::cout << "The purchased time for this meter is "
              << meter->getMinutesPurchased() << " minutes.\n"
              << "What do you want to do?\n"
              << "1. Inspect the car.\n"
              << "2. Write a ticket.\n"
              << "3. Move along... (ignore this car).\n";

    int selection = getMenuSelection(3);

    switch (selection) {
        case 1:
            inspectCar();
            break;
        case 2:
            writeTicket();
            break;
        case 3:
            moveAlong();
            break;
    }
}

/**
 * Attempts to write a ticket for our ParkedCar.
 * If we do not have the information about the car recorded, we will be required
 * to enter the information about the car before we can write a ticket.
 * If the car is not illegally parked, we will be forced to move along to the
 * next car.
 */
void Simulator::writeTicket() {
    if (car->incompleteInformation()) {
        std::cout << "You need to record the car information first.\n";
        recordCarInformation();
    }
    else {
        ParkingTicket * ticket = nullptr;

        try {
            ticket = officer->issueTicket(car, meter);
            successfulTicket(ticket);
        }
        catch (const ParkingTicket::NoViolation &ex) {
            unsuccessfulTicketAttempt();
        }
        delete ticket;
        moveAlong();
    }
}

/**
 * Displays the ticket that we have written to the user and saves it to the
 * ticket book.
 * @param ticket The ticket we have created.
 */
void Simulator::successfulTicket(ParkingTicket * ticket) {
    std::cout << "Success! You wrote a ticket. Here is what it looks like:\n\n";
    ticket->printTicket(std::cout);
    std::cout << std::endl;
    try {
        std::ofstream ticketBook;
        ticketBook.open(FILE_NAME, std::ios::app);
        ticket->printTicket(ticketBook);
        ticketBook.close();
    }
    catch (const std::exception &ex) {
        std::cout << "There was an error saving the ticket to file.\n";
    }
}

/**
 * Displays a message to user that a ticket cannot be created and we should move on.
 */
void Simulator::unsuccessfulTicketAttempt() {
    std::cout << "You cannot write a ticket for a car that is legally parked!\n"
              << "That would be extremely unethical...\n";
}

/**
 * Displays a message that we move along in our patrol.
 */
void Simulator::moveAlong() {
    std::cout << "You decide to move on to the next parked car...\n\n";
}

/**
 * Gets a random integer value from 0 to MAX_MINUTES (not inclusive).
 * @return A random integer value.
 */
int Simulator::getRandomInt() {
    return rand() % MAX_MINUTES;
}

/**
 * Gets string input from a user and sets display formatting.
 * @param inputMsg Information about what value we want to receive from the user.
 * @return the user input as a string.
 */
std::string Simulator::getStringInput(const std::string &inputMsg) {
    std::cout << "Enter " << inputMsg << ":\n"
              << "Enter '" << QUIT << "' at any time to exit.\n";
    std::string input;
    std::cout << "\n>> ";
    std::getline(std::cin, input);
    std::cout << std::endl;
    input = trim(input);
    if (toLower(input) == QUIT) {
        throw QuitException();
    }
    return input;
}

/**
 * Gets a menu selection from the user.
 * This method will recur if bad input is received.
 * @param maxMenu The max menu number.
 * @return The integer menu selection of the user.
 */
int Simulator::getMenuSelection(int maxMenu) {
    int selection = getIntegerInput("menu selection");
    if (selection < 1 || selection > maxMenu) {
        std::cout << "Sorry, that was not a valid menu selection.\n"
                  << "Please enter a menu option from 1 to " << maxMenu << "\n";
        return getMenuSelection(maxMenu);
    }
    return selection;
}

/**
 * Gets an string input from the user and returns it as an integer (if possible).

 * @param inputType Information about the input we want to receive.
 * @return User input as an integer.
 */
int Simulator::getIntegerInput(const std::string &inputType) {
    std::string userInput = getStringInput(inputType);
    int result;
    try {
        result = stoi(userInput);
        return result;
    }
    catch (const std::exception &ex) {
        std::cout << "That was not a valid integer value.\n";
        return getIntegerInput();
    }
}

/**
 * For getting an integer value without any additional information.
 * @return User input as an integer.
 */
int Simulator::getIntegerInput() {
    return getIntegerInput("an integer value");
}


