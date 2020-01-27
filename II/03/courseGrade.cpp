/*
    Stephen Gerkin
    DATE 2019-09-02
    CIST 2362 - C++ II
    CRN 22282
    Programing Lab 03
    Course Grades
    PROGRAM PROMPT
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "InputValidation.h"
#include "StudentCourseGrade.h"

// function declarations
void courseGrade();
unsigned int getValidIntegerInput(const std::string &);
void constructStudentCourseGrade(StudentCourseGrade &, unsigned int &);
std::string getStudentName(const unsigned int &);
double getTestScore(const int &);
double calculateAverage(const double *, const unsigned int &);
char determineGrade(const double &);
void displayStudentGrades(const StudentCourseGrade *, const int &);
void printLineBreak(const int &);
bool repeatProgram();


int main() {
    while (true) {
        system("cls");
        courseGrade();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

/**
*   CourseGrade

*/
void courseGrade() {
    // function to construct StudentCourseGrade structure elements for storing
    // and displaying information about students

    // get number of tests and students from the user and allocate an array
    // of StudentCourseGrade structures to store the information
    std::string outMsg = "How many test scores are to be entered?";
    unsigned int numTests = getValidIntegerInput(outMsg);
    
    outMsg = "How many students are to be entered?";
    unsigned int numStudents = getValidIntegerInput(outMsg);

    StudentCourseGrade *students = new StudentCourseGrade[numStudents];

    // get the information for each student
    for (unsigned int i = 0; i < numStudents; i++) {
        (students + i)->idNum = i + 1000;
        constructStudentCourseGrade(*(students+i), numTests);
    }
    
    displayStudentGrades(students, numStudents);

    // free memory for the StudentCourseGrade array
    delete[] students;
}

unsigned int getValidIntegerInput(const std::string &outMsg) {
    // displays outMsg to console to get an integer value from the user
    // does not allow values less than or equal to 0

    std::string userInput;

    while (true) {
        std::cout << outMsg << "\n>> ";
        std::getline(std::cin, userInput);
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

void constructStudentCourseGrade(StudentCourseGrade &studentCourseGrade,
                                 unsigned int &numTests) {
    // populates a StudentCourseGrade structure with data

    studentCourseGrade.name = getStudentName(studentCourseGrade.idNum);
    studentCourseGrade.testScores = new double[numTests];
    for (unsigned int i = 0; i < numTests; i++) {
        studentCourseGrade.testScores[i] = getTestScore(i+1);
    }
    studentCourseGrade.average = calculateAverage(studentCourseGrade.testScores,
                                                  numTests);
    studentCourseGrade.grade = determineGrade(studentCourseGrade.average);
}


std::string getStudentName(const unsigned int &idNum) {
    // gets user input for student name corresponding to the ID Number
    // does not allow empty strings

    std::string userInput;

    while (true) {
        std::cout << "Enter the name of student for ID# " << idNum << "\n>> ";
        std::getline(std::cin, userInput);
        std::cout << std::endl;

        if (userInput.size() <= 0) {
            std::cout << "Student name cannot be empty." << std::endl;
        }
        else {
            break;
        }
    }
    
    return userInput;
}

double getTestScore(const int &testNumber) {
    // gets a test score from the user
    // does not allow negative numbers

    std::string userInput;
    while (true) {
        std::cout << "Enter the score for test #" << testNumber << "\n>> ";
        std::getline(std::cin, userInput);
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

double calculateAverage(const double *arr,
                        const unsigned int &arrSize) {
    // calculates the average of the values in a double array and returns result

    double sum = 0;

    for (unsigned int i = 0; i < arrSize; i++) {
        sum += *(arr + i);
    }

    return sum / arrSize;
}

char determineGrade(const double &average) {
    // takes an average score and returns the character representation of grade

    if (average <= 60) {
        return 'F';
    }
    if (average <= 70) {
        return 'D';
    }
    if (average <= 80) {
        return 'C';
    }
    if (average <= 90) {
        return 'B';
    }
    // if we get here, average is an A
    return 'A';
}

void displayStudentGrades(const StudentCourseGrade *students,
                          const int &numStudents) {
    // prints all students stored by StudentCourseGrade array to screen

    // for printing display header
    const int FIELDS = 4;
    std::string fields[FIELDS] {"Student ID",
                                "Student Name",
                                "Average",
                                "Grade"};
    std::string fieldBreak = " | ";

    // designate a length for each line and calculate the length of each printed
    // field, no field except name should exceed the characters in the field
    // name
    const int LINE_LEN = 80;
    int idLength = fields[0].size();
    int avgLength = fields[1].size();
    int gradeLength = fields[2].size();
    
    // name length is what is left over minus field breaks, no field break at
    // the end of a line
    int nameLength = LINE_LEN - (idLength + avgLength + gradeLength);
    nameLength -= fieldBreak.size() * (FIELDS - 1);
    
    printLineBreak(LINE_LEN);

    {
        using namespace std; // for some added readability

        // print header
        cout << right << setw(idLength) << fields[0] << fieldBreak
            << left << setw(nameLength) << fields[1] << fieldBreak
            << setw(avgLength) << fields[2] << fieldBreak
            << setw(gradeLength) << fields[3];

        printLineBreak(LINE_LEN);

        // print each student
        for (int i = 0; i < numStudents; i++) {
            cout << right << setw(idLength) << students->idNum << fieldBreak
                << left << setw(nameLength) << students->name << fieldBreak
                // avg display requires more modification
                << setw(avgLength) << setprecision(2) << fixed << showpoint 
                << students->average << fieldBreak
                << setw(gradeLength) << students->grade;

            printLineBreak(LINE_LEN);

            // increment pointer to go to next student
            students++;
        }
    }// end using namespace std
}

void printLineBreak(const int &charsPerLine) {
    // for seperating between elements in a printed table

    

    std::cout << std::endl;
    for (int i = 0; i < charsPerLine; i++) {
        std::cout << "-";
    }
    std::cout << std::endl;
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