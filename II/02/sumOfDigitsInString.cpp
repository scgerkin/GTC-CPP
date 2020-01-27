/*
    Stephen Gerkin
    2019/08/21
    CIST 2362 - C++ II
    CRN 22282
    Programing Lab 02
    Sum of Digits in a String
    Write a program that asks the user to enter a series of single-digit numbers
    with nothing separating them. Read the input as a C-string or a string
    object. The program should display the sum of all the single-digit numbers
    in the string. For example, if the user enters 2514, the program should
    display 12, which is the sum of 2, 5, 1, and 4. The program should also
    display the highest and lowest digits in the string
*/
#include <iostream>
#include <regex>
#include <sstream>

// function declarations
void sumOfDigitsInString();
std::string getStringOfNumbers();
bool validUnsignedInteger(const std::string &input);
int * sliceStringIntoIntegerArray(const std::string &str);
bool repeatProgram();
bool validYN(const std::string &);

int main() {
    while (true) {
        system("cls");
        sumOfDigitsInString();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

void sumOfDigitsInString() {
    // gets a string of numbers from a user
    // calculates the sum of the numbers in the string and finds the lowest
    // and highest numbers entered
    // then displays them

    // get user input
    std::string stringOfNumbers = getStringOfNumbers();

    // break string up into an array of integers
    int * arrIterator = sliceStringIntoIntegerArray(stringOfNumbers);
    // hold onto the beginning of the array
    const int * beginningOfArr = arrIterator;

    // vars to store what we need to display
    int sum = 0;
    int lowest = 9;
    int highest = 0;

    // iterate over the array until pointing to -1
    while (*arrIterator > -1) {
        // grab lowest
        if (*arrIterator < lowest) {
            lowest = *arrIterator;
        }

        // grab highest
        if (*arrIterator > highest) {
            highest = *arrIterator;
        }

        sum += *(arrIterator);
        arrIterator++;
    }

    // free the memory
    delete[] beginningOfArr;

    // display results
    std::cout << "The sum of your string is: " << sum << std::endl
        << "The highest number you entered was: " << highest << std::endl
        << "The lowest number you entered was: " << lowest << std::endl;
}

std::string getStringOfNumbers() {
    // gets a string of numbers from the user, does not allow anything except
    // integer values for each element of the string

    std::string userInput;
    while (true) {
        std::cout << "Enter a string of numbers with no seperations.\n>> ";
        std::getline(std::cin, userInput);

        if (validUnsignedInteger(userInput)) {
            break;
        }
        else {
            std::cout << "That was not a valid entry.\n"
                << "Please enter only numbers.\n\n";
        }
    }

    return userInput;
}

bool validUnsignedInteger(const std::string &input) {
    // verifies that string input is only an unsigned integer
    std::regex pattern("(^[0-9]+[0-9]*$)");
    return std::regex_match(input, pattern);
}

int * sliceStringIntoIntegerArray(const std::string &str) {
    // slices a string of numbers into an array of integers

    // get length of string
    unsigned int strLength = str.length();

    // create an array to hold the numbers with room for a termination flag
    int *arr = new int[strLength + 1];

    // iterate over string to get numbers using substr() to get only one number
    for (unsigned int i = 0; i < strLength; i++) {
        *(arr + i) = std::stoi(str.substr(i, 1));
    }
    // end the arr with -1 as a flag
    *(arr + strLength) = -1;

    return arr;
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
