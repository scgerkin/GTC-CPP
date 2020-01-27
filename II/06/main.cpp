
#include <iostream>
#include <string>
#include <regex>

// prototypes
void startDemo();
bool repeatProgram();

/**
 * \brief Main method entry point for program.
 */
int main() {
    while (true) {
        startDemo();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

/**
 * \brief Function to repeat program.
 * Displays prompt to user asking if they would like to repeat the program.
 * Waits for input consisting of "y" or "n" (case insensitive).
 * \return True if user wants to repeat program.
 */
bool repeatProgram() {
    std::string input;

    while (true) { // loop until valid y/n entry
        std::cout << "\n\nDo you want to run the program again? (y/n)\n>> ";
        std::getline(std::cin, input);

        std::regex pattern("([Y|N])", std::regex_constants::icase);

        if (std::regex_match(input, pattern)) {
            break; // end loop
        }
        else {
            std::cout << "That was not a recognized entry.\n"
                << "Please enter only 'y' or 'n'" << std::endl;
        }
    }
    return input == "Y" || input == "y";
}