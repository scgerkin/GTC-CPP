#include "Demonstration.h"

#include <iostream>

const std::string Demonstration::QUIT_STR = "quit"; // string to terminate demo

/**
 * Constructor initiates the demonstration program.
 */
Demonstration::Demonstration() {
    displayIntroMsg();
    std::string userInput = this->getUserInput();
    while (userInput != QUIT_STR) {
        displayIsBalanced(userInput);
        userInput = getUserInput();
    }
}

/**
 * Displays an introductory message to the user explaining how the program works.
 */
void Demonstration::displayIntroMsg() {
    using std::cout;
    cout << "This program will test for parentheses balance in a string\n"
         << "Balanced is achieved when every right, closing parenthesis ')'\n"
         << "is preceded by a left, opening parenthesis '('\n"
         << "and every opened parenthesis is closed.\n"
         << "For example, ()() or (()) is balanced but )( or (() is not.\n";
}

/**
 * Gets input from the user and formats the terminal for spacing.
 * Also displays a message to the user requesting input.
 * @return Returns the user input as a string.
 */
std::string Demonstration::getUserInput() {
    std::cout << "Enter a string to test for balance (to quit type \""
              << QUIT_STR
              << "\"):\n>> ";
    std::string input;
    std::getline(std::cin, input);
    std::cout << std::endl;
    return input;
}

/**
 * Checks if a string is balanced for parentheses and prints the result of
 * using the StringChecker::isBalanced method to the terminal
 * @param str The string we are to check.
 */
void Demonstration::displayIsBalanced(const std::string &str) {
    bool isBalanced = StringChecker::isBalanced(str);

    std::cout << ((isBalanced) ? "Yes" : "No")
              << ", that string is "
              << ((isBalanced) ? "" : "not ")
              << "balanced.\n";
}
