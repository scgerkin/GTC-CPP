/*
Name: Stephen Gerkin
Date: 03/08/2019
Lesson 9 Program 1
Program Title:
    Account Number Validator
Program Description:
    Program checks a value entered by the user against values in an array
    Displays whether or not the value was found
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// function prototypes
void
    insertionSort(int[], int);          // insertion sort function
int
    binarySearch(int[], int, int),      // binary search function
    getUserInput();                     // function get get user input

/*
* Main function body
*/
int main() {
    const int ARR_SIZE = 18;    // constant for size of array
    
    // declare and init aray
    int existingAcctNo[ARR_SIZE] =
        {
        5658845, 4520125, 7895122, 8777541, 8451277, 1302850,
        8080152, 4562555, 5552012, 5050552, 7825877, 1250255,
        1005231, 6545231, 3852085, 7576651, 7881200, 4581002
        };
    
    int searchValue;    // var for value to search for
    int foundLoc;       // location for value in array

    // entrance msg
    cout << "Welcome to the charge account number validator." << endl << endl;
    
    // sort the array
    insertionSort(existingAcctNo, ARR_SIZE);

    // get value to search for
    searchValue = getUserInput();

    // search for value
    foundLoc = binarySearch(existingAcctNo, ARR_SIZE, searchValue);

    // display relevant message for value entered
    if (foundLoc == -1) {
        cout << "The value you entered, "<< searchValue << ", was not found.";
    }
    else {
        cout << "The value you entered, " << searchValue << ", is valid.";
    }

    // exit msg
    cout << endl << endl << "Program complete." << endl << endl;

    // terminate
    system("pause");
    return 0;
}

/*
* Name:
*   getUserInput
* Parameters:
*   none
* Return:
*   int     user input as an integer
* Description:
*   Gets user input and returns it
*/
int getUserInput() {
    string userInput;

    cout << "Enter the account number you want to search for: ";
    getline(cin, userInput);

    cout << endl;

    return stoi(userInput);
}

/*
* Name:
*   insertionSort
* Parameters:
*   int[]   intArr      integer array to sort
*   int     arraySize   size of array to sort
* Return:
*   none
* Description:
*   Insertion sort function for integer array, sorts in ascending order
*/
void insertionSort(int intArr[], int arraySize) {
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
*   binarySearch
* Parameters:
*   int[]   arr         array to search
*   int     arrSize     size of array to search
*   int     value       value to search for
* Return:
*   int     location of value to search for in array
* Description
*   Binary search function. Returns the index for an element if found in array
*   otherwise returns -1 for elements not found in array.
*/
int binarySearch(int arr[], int arrSize, int value) {
    int first = 0;
    int last = arrSize - 1;
    int middle;

    // while there are values are to search for
    while (first <= last) {
        // determine middle of search area
        middle = first + (last - first) / 2;

        // if value is at middle point, return index
        if (arr[middle] == value) {
            return middle;
        }

        // if value greater, ignore top half 
        if (arr[middle] < value) {
            first = middle + 1;
        }
        // otherwise ignore bottom half 
        else {
            last = middle - 1;
        }
    }

    // return -1 if not found
    return -1;
}