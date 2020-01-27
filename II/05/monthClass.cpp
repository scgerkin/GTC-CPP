#include <iostream>
#include <string>
#include <regex>
#include "Month.h"

void monthClass();
bool repeatProgram();

/**Main entry point for program.*/
int main() {
    while (true) {
        system("cls");
        monthClass();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

/** Demonstrates the Month class.
Initializes a new Month object with no arguments.
Then demonstrates post/prefix increment/decrements and input stream allowing
either number or name entry.
*/
void monthClass() {
    Month month;

    std::cout << "The current month is...\n" << month << std::endl;
    
    // prefix increment
    std::cout << "The next month is...\n" << ++month << std::endl;

    // postfix increment
    std::cout << "Month is being incremented.\n" << month++ << std::endl;
    std::cout << "After increment:\n" << month << std::endl;

    // prefix decrement
    std::cout << "The previous month is...\n" << --month << std::endl;

    // postfix decrement
    std::cout << "Month is being decremented.\n" << month-- << std::endl;
    std::cout << "After decrement:\n" << month << std::endl;

    std::cout << std::endl;
    
    std::cout << "Looping through the months...\n\n";

    // loop through all months showing reset after 12
    for (int i = 0; i < 13; i++) {
        std::cout << ++month;
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Reversing through the months...\n\n";

    // reverse it
    for (int i = 0; i < 13; i++) {
        std::cout << --month;
        std::cout << std::endl;
    }
    
    // input stream operators
    std::cout << std::endl;
    std::cout << "Enter a month number (ie 7)\n>> ";
    std::cin >> month;
    std::cout << std::endl << "That month is " << month << std::endl;

    std::cout << std::endl;
    std::cout << "Enter a month full month name (ie July)\n>> ";
    std::cin >> month;
    std::cout << std::endl << "That month is " << month << std::endl;
}

/** Function to repeat program.
Displays prompt to user asking if they would like to repeat the program.
Waits for input consisting of "y" or "n" (case insensitive).

@return True if user wants to repeat program.
*/
bool repeatProgram() {
    std::string userInput;

    while (true) { // loop until valid y/n entry
        std::cout << "\n\nDo you want to run the program again? (y/n)\n>> ";
        std::cin >> std::ws;
        std::getline(std::cin, userInput);

        const static std::regex pattern("([Y|N])", std::regex_constants::icase);
        if (std::regex_match(userInput, pattern)) {
            break; // end loop
        }
        else {
            std::cout << "That was not a recognized entry.\n"
                << "Please enter only 'y' or 'n'" << std::endl;
        }
    }
    return userInput == "Y" || userInput == "y";
}