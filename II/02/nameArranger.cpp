/*
    Stephen Gerkin
    2019/08/21
    CIST 2362 - C++ II
    CRN 22282
    Programing Lab 02
    Name Arranger
    Write a program that asks for the user�s first, middle, and last names. The
    names should be stored in three different character arrays. The program
    should then store, in a fourth array, the name arranged in the following
    manner: the last name followed by a comma and a space, followed by the first
    name and a space, followed by the middle name. For example, if the user
    entered "Carol Lynn Smith", it should store "Smith, Carol Lynn" in the
    fourth array. Display the contents of the fourth array on the screen.
*/
#include <iostream>
#include <regex>
#include "Name.h" // Name struct

// function declarations
void nameArranger();
Name getName(const std::string &);
bool repeatProgram();
bool validYN(const std::string &);


int main() {
    while (true) {
        system("cls");
        nameArranger();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

void nameArranger() {
    // function to get first, middle, and last name from user
    // then combine them into one full name with comma/space seperators

    // get first, middle, and last name
    Name first = getName("first");
    Name middle = getName("middle");
    Name last = getName("last");

    // combine them
    Name full(first, middle, last);

    // display results
    std::cout << "\nYour full name is: " << std::endl;
    full.printName();
}

Name getName(const std::string &position) {
    // gets a name from the user as a string, converts to c-string,
    // and then creates/returns a Name struct with the c-string and length of
    // the name

    // get input
    std::string userInput;
    std::cout << "Enter your " << position << " name (hit enter if none):\n>> ";
    std::getline(std::cin, userInput);

    // hold onto the length of the user input for iterating over string
    unsigned int nameLength = userInput.length();

    // create an array for the name
    char *cstrptr = new char[nameLength + 1];

    // copy string to c-string
    for (unsigned int i = 0; i < nameLength; i++) {
        *(cstrptr + i) = userInput[i];
    }
    // null terminate for safety
    *(cstrptr + nameLength) = NULL;

    // construct a Name structure and return
    return Name(cstrptr, nameLength);
}

bool repeatProgram() {
    // Checks if user wants to repeat main program loop.

    std::string userInput;

    while (true) { // loop until valid y/n entry
        std::cout << "\n\nDo you want to run the program again? (y/n)\n>> ";
        std::getline(std::cin, userInput);

        if (validYN(userInput)) {
            break; // end loop
        }
        else {
            std::cout << "That was not a recognized entry.\n"
                << "Please enter only 'y' or 'n'" << std::endl;
        }
    }
    return userInput == "Y" || userInput == "y";
}

bool validYN(const std::string &input) {
    // verifies that string input is only "Y" or "N", case insensitive
    std::regex pattern("([Y|N])", std::regex_constants::icase);
    return std::regex_match(input, pattern);
}
