/*
    Stephen Gerkin
    2019/08/21
    CIST 2362 - C++ II
    CRN 22282
    Programing Lab 02
    Word Counter
    Write a function that accepts a pointer to a C-string as an argument and
    returns the number of words contained in the string. For instance, if the
    string argument is "Four score and seven years ago" the function should
    return the number 6. Demonstrate the function in a program that asks the
    user to input a string then passes it to the function. The number of words
    in the string should be displayed on the screen.
    Optional Exercise: Write an overloaded version of this function that accepts
    a string class object as its argument.
*/
#include <iostream>
#include <regex>
#include <set>

// function declarations
void wordCounter();
char * getUserString();
int getNumWords(const char *);
bool repeatProgram();
bool validYN(const std::string &);

int main() {
    while (true) {
        system("cls");
        wordCounter();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

void wordCounter() {
    // main method for program to get a string of words from a user and display
    // how many words are in the string

    // get string
    char *stringPtr = getUserString();

    // calc num words
    int numWords = getNumWords(stringPtr);

    // display num words
    std::cout << "The number of words is " << numWords << std::endl;

    // free memory used by c-string
    delete[] stringPtr;
}

char * getUserString() {
    // gets user input as a string and converts it to a c-string and terminates
    // it with NULL
    // the array created must be deleted after processing is finished to free
    // memory

    // get input
    std::string userInput;
    std::cout << "Enter a string you want to word count:\n>> ";
    std::getline(std::cin, userInput);

    unsigned int strLength = userInput.length();

    // create a new empty c-string with room for null termination
    char *cStrPtr = new char[strLength + 1];

    // copy string to c-string
    for (unsigned int i = 0; i < strLength; i++) {
        *(cStrPtr + i) = userInput[i];
    }

    // null terminate
    *(cStrPtr + strLength) = NULL;

    return cStrPtr;
}

int getNumWords(const char *ptr) {
    // counts number of words in a c-string by iterating over a c-string
    // each time a delimiter is found, the next character is checked to be sure
    // it is not also a delimiter or the end of the string
    // the number of words is incremented if these conditions are satisfied

    // early return 0 if string is null
    if (*ptr == NULL) {
        return 0;
    }

    // set used to look for delimiters, more can be added easily if needed
    std::set<char> delimiters = {'.', ' ', '\n', '\t', '!', ',', '(', ')'};

    // init num words as 0 if string starts with a delimiter, o/w init as 1
    // uses set.count() to return 0 (false) if not in the set
    // set.count() is O(logn) so lookup is insignificant compared to complexity
    // of iterating over the string
    int numWords = (delimiters.count(*ptr)) ? 0 : 1;

    // while pointer value is not null
    while (*ptr) {
        // if current char is delimiter and next char is not null or delimiter
        if ((delimiters.count(*ptr)) &&
            *(ptr + 1) != NULL &&
            !delimiters.count(*(ptr+1)))
        {
            numWords++;
        }
        // go to next char
        ptr++;
    }

    return numWords;
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
