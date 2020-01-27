/*
Name: Stephen Gerkin
Date: 03/22/2019
Lesson 11 Program 1
Program Title:
    Movie Survey Data
Program Description:
    Program demonstrates a dynamically allocated array by asking the user to
    enter a number students surveyed. The program then gets the number of movies
    seen by each student, calculates the average, mean, and mode, and displays
    the results.
*/
#include <iostream>
#include "validate.h"
using namespace std;

// structure declarations
struct Stats {          // structure for stats of an array
    double average;     // var for average
    double median;      // var for median
    int mode;           // var for mode
};

// function prototypes
void                            // display functions 
    dispStartMsg(),             // displays start msg
    dispError(),                // displays error msg
    displayStats(Stats, int),   // displays stats
    dispExitMsg();              // displays exit msg

int                             // get functions
    getNumStudents(),           // gets number of students
    getNumMovies(int);          // gets number of movies

void                            // array functions
    insertionSort(int*, int);   // sorts array
double                          
    findAverage(int*, int),     // finds average of array
    findMedian(int*, int);      // finds median of array
int
    findMode(int*, int);        // finds mode of array

// main method
int main() {
    int numStudents;                    // var for number of students surveyed

    int *movies = nullptr;     // array to hold number of movies

    Stats movieStats;           // structure to hold the statistics of the array

    // start msg
    dispStartMsg();

    // get number of students surveyed
    numStudents = getNumStudents();

    cout << endl;

    // dynamically allocate array 
    movies = new int[numStudents];

    // get number of movies seen by each student
    for (int i = 0; i < numStudents; i++) {
        movies[i] = getNumMovies(i + 1);
    }

    // sort the array
    insertionSort(movies, numStudents);

    // get average
    movieStats.average = findAverage(movies, numStudents);

    // get median
    movieStats.median = findMedian(movies, numStudents);

    // get mode
    movieStats.mode = findMode(movies, numStudents);

    // display stats
    displayStats(movieStats, numStudents);

    // free memory
    delete[] movies;
    movies = nullptr;

    // exit msg
    dispExitMsg();

    // terminate
    system("pause");
    return 0;
}

/*
* Name:
*   displayStartMsg
* Parameters:
*   none
* Return:
*   none
* Description:
*   Function displays start message at beginning of program.
*/
void dispStartMsg() {
    cout << "Welcome to the movie survey data program." << endl
        << "This program will ask you how many students were surveyed" << endl
        << "and how many movies each student has seen in a month." << endl
        << "The program will then calculate the average, median, and" << endl
        << "mode for all students and display the results." << endl << endl;
}

/*
* Name:
*   dispError
* Parameters:
*   none
* Return:
*   none
* Description:
*   Function to display an error message if invalid input is entered
*/
void dispError() {
    cout << "\aInvalid Input!" << endl
        << "Valid input consists of positive integer." << endl << endl;
}

/*
* Name:
*   displayStats
* Parameters:
*   active      Stats structure containing the average, median, and mode of the
*               array
*   numSurveyed Number of students surveyed
* Return:
*   none
* Description:
*   Function displays the average, median, and mode of the elements entered into
*   the array of the program
*/
void displayStats(Stats active, int numSurveyed) {

    cout << endl
        << "The number of students surveyed was " << numSurveyed << "."
        << endl
        << "The average number of movies seen was " << active.average << "."
        << endl
        << "The median number of movies seen was " << active.median << "."
        << endl;

    // display mode if found, otherwise display no mode found
    if (active.mode >= 0) {
        cout << "The most common number (mode) of movies seen was "
            << active.mode << "." << endl;
    }
    else {
        cout << "Every student saw a unique number of movies. No mode found."
            << endl;
    }
}

/*
* Name:
*   dispExitMsg
* Parameters:
*   none
* Return:
*   none
* Description:
*   Function displays exit program message before termination
*/
void dispExitMsg() {
    cout << endl
        << "Thank you for using the movie survey data program." << endl
        << "The program is now finished and will end." << endl << endl;
}

/*
* Name:
*   getNumStudents
* Parameters:
*   none
* Return:
*   int     user input as integer
* Description:
*   Function gets number of students surveyed for creating array size
*/
int getNumStudents() {
    string userInput;   // var for user input

    // get input
    cout << "Enter the number of students surveyed: ";
    getline(cin, userInput);

    // if input not validated as unsigned int, display error and recur
    if (!regex_u_int(userInput)) {
        dispError();
        return getNumStudents();
    }

    // return input as integer
    return stoi(userInput);
}

/*
* Name:
*   getNumMovies
* Parameters:
*   student     the student # entry is being entered for
* Return:
*   int     user input as integer
* Description:
*   Function gets number of movies seen by a student
*/
int getNumMovies(int student) {
    string userInput;   // var for user input

    // get input
    cout << "Enter the number of movies seen by student #" << student << ": ";
    getline(cin, userInput);

    // if input not validated as unsigned int, display error and recur
    if (!regex_u_int(userInput)) {
        dispError();
        return getNumMovies(student);
    }

    // return input as integer
    return stoi(userInput);
}

/*
* Name:
*   insertionSort
* Parameters:
*   *intArr     pointer to an integer array
*   arraySize   size of the array to be sorted
* Return:
*   none
* Description:
*   Insertion sort to sort an array of integer type
*/
void insertionSort(int *intArr, int arraySize) {
    int minIndex;   // temp var for index of lowest found value during scan
    int tempInt;    // temp var for int value

    // scan array
    for (int i = 0; i < (arraySize - 1); i++) {
        minIndex = i;
        tempInt = intArr[i];

        // move array elements
        for (int j = i + 1; j < arraySize; j++) {
            if (intArr[j] < tempInt) {

                tempInt = intArr[j];
                minIndex = j;
            }
        }

        // insert value to position
        intArr[minIndex] = intArr[i];
        intArr[i] = tempInt;
    }
}

/*
* Name:
*   findAverage
* Parameters:
*   *arr        pointer to array of integers
*   size        size of array
* Return:
*   double      average of array
* Description:
*   Function takes a sorted integer array and finds the average of all the
*   elements in the array
*/
double findAverage(int *arr, int size) {
    double average = 0;     // var for storing the average

    // add every element of the array
    for (int i = 0; i < size; i++) {
        average += arr[i];
    }

    // divide by size of array
    average /= size;

    // return average
    return average;
}

/*
* Name:
*   findMedian
* Parameters:
*   *arr        sorted array to search
*   size        size of the array
* Return:
*   double      value of the median value in the array
* Description:
*   Function takes an array and finds the median value of it. If the array has
*   an odd number of elements, the element in the middle index of the array is
*   returned. Otherwise, if the array has an even number of elements, the median
*   is calculated by adding the values of 2 middle elements and dividing by 2
*/
double findMedian(int *arr, int size) {
    int median;     // var for median

    // decrement size for use in decision structure
    size--;

    // if the max index # is even,
    // the array has an odd number of elements
    // return the value in the middle of the array
    if (size % 2 == 0) {
        median = arr[size / 2];
    }
    // otherwise, the array has an even number of elements
    else {
        // the median is the value of the two middle elements added and
        // divided by 2
        median = (arr[((size - 1) / 2)] + arr[((size - 1) / 2) + 1]) / 2;
    }

    // return the median
    return median;
}

/*
* Name:
*   findMode
* Parameters:
*   *arr        sorted array to scan for mode
*   size        size of array to scan
* Return:
*   int     value of the mode found
* Description:
*   Function scans an integer array to find the mode of the array. If no mode is
*   found, the function will return -1 to indicate no mode was found. Only works
*   for an array of positive numbers
*/
int findMode(int *arr, int size) {
    int mode = -1;              // init mode as -1, if no mode is found
                                // this value will be returned to signify
                                // no mode was found: each element was unique

    int modeCount = 1;          // init count as 1

    int possibleMode = 0;       // temp var used for scanning array
    int iterationCount = 0;     // accumulator while scanning array

    // scan array by each element
    for (int i = 0; i < size; i++) {
        // set the iteration count to 0 for each loop
        iterationCount = 0;

        // set temp var to value in the index of the iteration
        possibleMode = arr[i];

        // compare the temp var to each value in the array
        for (int j = 0; j < size; j++) {

            // if the temp var is found in the array, increment accumulator
            if (possibleMode == arr[j]) {
                iterationCount++;
            }
        }

        // if the temp value was found more than last check,
        // set mode to temp value
        // set mode count to iteration count, for next check comparison
        if (iterationCount > modeCount) {
            modeCount = iterationCount;
            mode = possibleMode;
        }
    }

    // return mode if found, return -1 if no mode found
    return mode;
}