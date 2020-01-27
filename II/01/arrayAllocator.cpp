/*
    Stephen Gerkin
    2019/08/15
    CIST 2362 - C++ II
    CRN 22282
    Programming Lab 01
    Array Allocator
    Write a function that dynamically allocates an array of integers. The
    function should accept an integer argument indicating the number of elements
    to allocate. The function should return a pointer to the array.
*/
#include <iostream>
#include <string>
#include <regex>

// function declarations - listed in program call order
void arrayAllocator();
unsigned int getArraySize();
bool validUnsignedInt(const std::string &);
int * createArrayOfSize(const int &);
void deleteArray(const int *);
bool repeatProgram();
bool validYN(const std::string &);


int main() {
    while (true) {
        system("cls");
        arrayAllocator();
        if (!repeatProgram()) {
            break;
        }
    }

    // terminate
    return 0;
}

void arrayAllocator() {
    // gets an integer value from the user and creates an array of the specified
    // size, populates the array with values, then frees the memory of the array

    // get arraySize to use for array
    int arraySize = getArraySize();

    // create an array and get the pointer
    int *arr = createArrayOfSize(arraySize);

    std::cout << "Array created" << std::endl;

    // populate array with some values
    for (int i = 0; i < arraySize; i++) {
        *(arr+i) = i + 5;
    }

    std::cout << "Array filled" << std::endl;

    // free memory
    deleteArray(arr);

    std::cout << "Array deleted" << std::endl;
}

unsigned int getArraySize() {
    // gets an integer value to use as array size from user
    // validates input to only allow integer values above 0


    unsigned int arraySize = 0;
    std::string userInput;

    while (arraySize < 1) {
        std::cout << "Enter the size desired for array:\n>> ";
        std::cin >> userInput;
        std::cout << std::endl;

        if (!validUnsignedInt(userInput) || std::stoul(userInput) == 0) {
            std::cout << "That was not a valid entry.\n"
                << "Please enter only an integer above 0." << std::endl;
            arraySize = 0;
        }
        else {
            arraySize = std::stoul(userInput);
        }
    }
    return arraySize;
}

bool validUnsignedInt(const std::string &input) {
    // verifies that string input is an unsigned integer
    std::regex pattern("(^[0-9]+[0-9]*$)");
    return std::regex_match(input, pattern);
}

int * createArrayOfSize(const int &size) {
    // creates an array of parameter arraySize and returns a pointer to the
    // array location in memory
    int *arr = new int[size];
    return arr;
}

void deleteArray(const int *arr) {
    // deletes an array at memory location from parameter
    // this is to demonstrate passing a pointer as a parameter to a function
    delete[] arr;
}

bool repeatProgram() {
    // Checks if user wants to repeat main program loop.

    std::string userInput;

    while (true) { // loop until valid y/n entry
        std::cout << "Do you want to run the program again? (y/n)\n>> ";
        std::cin >> userInput;

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
    // verifies that string input is only "Y", "y", "N", or "n"
    std::regex pattern("([Y|N|y|n])");
    return std::regex_match(input, pattern);
}
