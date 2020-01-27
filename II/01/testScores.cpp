/*
    Stephen Gerkin
    2019/08/16
    CIST 2362 - C++ II
    CRN 22282
    Programming Lab 01
    Test Scores #1
    Write a program that dynamically allocates an array large enough to hold a
    user-defined number of test scores. Once all the scores are entered, the
    array should be passed to a function that sorts them in ascending order.
    Another function should be called that calculates the average score. The
    program should display the sorted list of scores and averages with
    appropriate headings. Use pointer notation rather than array notation
    whenever possible.
    Input Validation: Do not accept negative numbers for test scores.
*/
#include <iostream>
#include <iomanip>
#include <regex>

// function declarations
void testScores();
unsigned int getNumTestScores();
bool validUnsignedInt(const std::string &);
double getTestScore(const int &);
bool validUnsignedFloat(const std::string &);
void sortArrayAscending(double *, const unsigned int &);
double calculateAverage(double *, const unsigned int &);
void displayResults(double *, const unsigned int &, const double &);
bool repeatProgram();
bool validYN(const std::string &);


int main() {
    // driver function calls program functio
    // repeats until user indicates they want to end

    while (true) {
        system("cls");
        testScores();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

void testScores() {
    // main function of program
    // gets the number of test scores to enter
    // gets test scores
    // sorts the test scores
    // calcs the average
    // displays results

    // create array to store the scores
    unsigned int numTestScores = getNumTestScores();
    double *testScoreValues = new double[numTestScores];//fixme make this double

    // fill array
    for (unsigned int i = 0; i < numTestScores; i++) {
        *(testScoreValues+i) = getTestScore(i+1);
    }

    // sort the array
    sortArrayAscending(testScoreValues, numTestScores);

    // calculate the average score
    double averageScore = calculateAverage(testScoreValues, numTestScores);

    // display the results
    displayResults(testScoreValues, numTestScores, averageScore);

}

unsigned int getNumTestScores() {
    // gets an integer value to use as array size from user
    // validates input to only allow integer values above 0

    unsigned int numTestScores = 0;
    std::string userInput;

    while (true) {
        std::cout << "How many test scores do you want to enter?\n>> ";
        std::cin >> userInput;
        std::cout << std::endl;

        if (!validUnsignedInt(userInput) || std::stoul(userInput) == 0) {
            std::cout << "That was not a valid entry.\n"
                << "Please enter only an integer above 0." << std::endl;
        }
        else {
            break;
        }
    }
    return std::stoul(userInput);
}

bool validUnsignedInt(const std::string &input) {
    // verifies that string input is an unsigned integer
    std::regex pattern("(^[0-9]+[0-9]*$)");
    return std::regex_match(input, pattern);
}

double getTestScore(const int &testNumber) {
    // gets a test score from the user
    // does not allow negative numbers

    std::string userInput;
    while (true) {
        std::cout << "Enter the score for test #" << testNumber << "\n>>";
        std::cin >> userInput;
        std::cout << std::endl;

        if (!validUnsignedFloat(userInput)) {
            std::cout << "That was not a valid entry.\n"
                << "Please enter a valid positive number value."
                << std::endl << std::endl;
        }
        else {
            break;
        }
    }

    return std::stod(userInput);
}

bool validUnsignedFloat(const std::string &input) {
    // validates unsigned float/double input
    std::regex pattern("([0-9]+)(\\.(([0-9]+)?))?");
    return std::regex_match(input, pattern);
}

void sortArrayAscending(double *arr,
                        const unsigned int &arrSize) {
    // ascending insertion sort

    // for storing array positions
    unsigned int i, j;

    // for storing value at current array location
    double value;

    // traverse array
    for (i = 1; i < arrSize; i++) {
        value = *(arr+i);   // grab value at current index
        j = i - 1;          // start sorting from index - 1

        // move elements
        while (j >= 0 && *(arr + j) > value) { // while val is below next val
            *(arr + j + 1) = *(arr + j);    // move element from jindex + 1 to
            j--;                            // previous jindex and decrement j
        }
        *(arr + j + 1) = value;             // put value back in array
    }
}

double calculateAverage(double *arr,
                        const unsigned int &arrSize) {
    // calculates the average of the values in a double array and returns result

    double sum = 0;

    for (unsigned int i = 0; i < arrSize; i++) {
        sum += *(arr + i);
    }

    return sum/arrSize;
}

void displayResults(double *sortedTestScores,
                    const unsigned int &numTestScores,
                    const double &average) {
    // displays the values in an array in order of index and average value of
    // the array

    std::cout << "The test scores in ascending order are..." << std::endl;

    for (unsigned int i = 0; i < numTestScores; i++) {
        std::cout << i + 1 << ". " << std::fixed << std::setprecision(2)
            << *(sortedTestScores + i) << "%" << std::endl;
    }

    std::cout << "The average score is " << std::fixed << std::setprecision(2)
        << average << "%" << std::endl;
}



bool repeatProgram() {
    // Checks if user wants to repeat main program loop.

    std::string userInput;

    while (true) { // loop until valid y/n entry
        std::cout << "\n\nDo you want to run the program again? (y/n)\n>> ";
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
