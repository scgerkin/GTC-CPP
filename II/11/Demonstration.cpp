#include "Demonstration.h"
#include "StringTools.h"
#include <iostream>
#include <algorithm>
#include <cmath>

const std::string Demonstration::QUIT = "quit";

/**
 * Starts the demonstration.
 * Loops the makeChange() function to demonstrate until the user indicates the
 * desire to quit.
 */
void Demonstration::start() {
    displayWelcomeMsg();
    while (true) {
        getMoney();
    }
}

/**
 * Displays a welcome message to the user about how the program will work.
 */
void Demonstration::displayWelcomeMsg() {
    using std::cout;
    // set up a demonstration of output
    changeMaker.makeChange(1559, 2000);
    cout << "Welcome to the ChangeMaker program demonstration.\n"
         << "This program will demonstrate a recursive algorithm that determines\n"
         << "how to make change for a purchase.\n"
         << "You will be asked for an amount owed for an item and then\n"
         << "an amount tendered by the customer.\n"
         << "The program will then determine how to make change for these amounts\n"
         << "and display the result.\n"
         << "For example, here is the display you will receive if you enter the\n"
         << "amount owed is $15.59 and the customer gives you a $20 bill.\n"
         << "\n" << changeMaker.getChangeStr()
         << "\nIf you enter too many decimal values (0.001), the value you entered\n"
         << "will be rounded as appropriate.\n\n";
}

/**
 * Demonstrates the ChangeMaker makeChange function by getting an amount owed
 * from the user and an amount tendered then displaying the string created.
 */
void Demonstration::getMoney() {
    int owed = getCurrency("the amount the customer owes");
    int tendered = getCurrency("the amount the customer tendered");
    makeChange(owed, tendered);
}

/**
 * Gets more money from the user if the amount owed is more than tendered.
 * @param owed The current amount owed.
 * @param tendered The current amount tendered to us.
 */
void Demonstration::getMoreMoney(int owed, int tendered) {
    std::cout << "The customer still owes money!\n";
    tendered += getCurrency("additional amount the customer tenders");
    makeChange(owed, tendered);
}

/**
 * Attempts to use the ChangeMaker::makeChange() function.
 * If it fails, this is because the customer has not given enough money and this
 * function will call the function to get more money.
 * @param owed The amount owed.
 * @param tendered The amount tendered.
 */
void Demonstration::makeChange(int owed, int tendered) {
    try {
        changeMaker.makeChange(owed, tendered);
        std::cout << changeMaker.getChangeStr();
        std::cout << std::endl;
    }
    catch (const ChangeMaker::NoChangePossible &ex) {
        getMoreMoney(owed, tendered);
    }
}

/**
 * Gets string input from a user and sets display formatting.
 * @param inputMsg Information about what value we want to receive from the user.
 * @return the user input as a string.
 */
std::string Demonstration::getStringInput(const std::string &inputMsg) {
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
 * Gets a currency value from the user. If invalid entry, will recur.
 */
int Demonstration::getCurrency(const std::string &what) {
    std::string userInput = getStringInput(what);
    double result;
    try {
        result = stod(userInput);
        if (result < 0) {
            throw std::exception();
        }
        return convertCurrencyToInteger(result);
    }
    catch (const std::exception &ex) {
        std::cout << "That was not a valid value.\n";
        return getCurrency(what);
    }
}

/**
 * Converts a double value for a dollar amount to integer with penny as base
 * (ie 20.00 is converted to 2000).
 */
int Demonstration::convertCurrencyToInteger(double amt) {
    amt *= 100;
    return (int) round(amt);
}
