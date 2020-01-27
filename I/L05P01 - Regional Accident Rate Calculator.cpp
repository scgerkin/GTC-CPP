/*

Name: Stephen Gerkin
Date: 02/05/2019
Lesson 5 Program 1
Program Title:
	Regional Accident Rate Calculator
Program Description:
	This program asks the user to enter the number of accidents for 5 regions and stores the info in an array
	It then sorts the array to determine the region with the least accidents and displays the name of the region
	If more than one region qualifies as the least accident prone, the program will display which regions are the least accident prone.

*/

#include <iostream>
#include <string>
#include <regex>
using namespace std;

// function prototypes
int
getNumAccidents(string);
void
findLowest(int[], string[]),
sort(int[], string[], int);
bool
validateInt(string);

// main body
int main() {

	int accidents[5];															// array for storing number of accidents
	string region[5]{"Northern", "Southern", "Eastern","Western","Central"};	// array for storing name of regions

	// entrance msg
	cout << "Welcome to the Regional Accident Rate Calculator!\n"
		"This program will ask you to enter the number of accidents for each region.\n"
		"It will then display the region with the lowest accidents.\n" << endl;

	// get accident numbers and store in array
	for (int i = 0; i <= 4; i++) {
		accidents[i] = getNumAccidents(region[i]);
	}

	// sort arrays
	sort(accidents, region, 5);

	// determine lowest accident region(s) and display result
	findLowest(accidents, region);

	// exit msg
	cout << "\nThanks for using the Regional Accident Rate Calculator!\n"
		"Don't become a statistic!" << endl;

	system("pause");
	return 0;
}

// get number of accidents for each region
// parameters: region name from region array
int getNumAccidents(string region) {

	string userInput;		// user input for regex check
	int numAccidents;		// user input converted to int

	// input loop with validation
	do {
		cout << "Enter the number of accidents for the " << region << " region: ";
		cin >> userInput;
		cout << endl;

		if (!validateInt(userInput)) {	// displays error if invalid input
			cout << "\aThat was not a valid number.\nPlease enter a positive integer.\n";
		}
	} while (!validateInt(userInput));	// loops until valid input

	numAccidents = stoi(userInput);		// convert input to datatype
	return numAccidents;				// return value
}

// selection sort for 2 parallel arrays
// transposed and adapted from a selection sort I wrote in VBA
// parameters: unsorted accidents array, parallel region array, size of the arrays
// sorts arrays in tandem in ascending order
void sort(int intArr[], string stringArray[], int arraySize) {

	int minIndex;		// temp variable for index location of lowest found value during scan iterations
	int tempInt;		// temp variable for int value in integer array
	string tempString;	// temp variable for string value in string array

	// scan the integer array
	for (int i = 0; i < (arraySize - 1); i++) {

		minIndex = i;
		tempInt = intArr[i];
		tempString = stringArray[i];

		// scan array starting at 2nd element looking for smallest value
		for (int j = i + 1; j < arraySize; j++) {
			if (intArr[j] < tempInt) {

				// store found values in temp for integer array and parallel string array
				tempInt = intArr[j];
				tempString = stringArray[j];

				minIndex = j;
			}
		}

		// move values in array
		intArr[minIndex] = intArr[i];
		intArr[i] = tempInt;

		// put temp value back into array
		stringArray[minIndex] = stringArray[i];
		stringArray[i] = tempString;
	}
}

// find and display lowest accident rate region(s)
// parameters: sorted accidents array w/ parallel sorted region array
void findLowest(int accidents[], string region[]) {

	// if statement to determine if there are any multiple regions with the same low accident number
	if (accidents[4] == accidents[0]) {																				// if accidents[4] is equal to accidents[0], all values are the same
		cout << "Each region had an equal amount of accidents of " << accidents[0] << ". Impressive!" << endl;
	}
	else if (accidents[3] == accidents[0]) {																		// if accidents[3] is equal to accidents[0], only one region has high value
		cout << "4 regions had equal accident rate of " << accidents[0] << ".\n"
			"The " << region[4] << " region had the most accidents with " << accidents[4] << " accidents." << endl;
	}
	else if (accidents[2] == accidents[0]) {																		// if accidents[2] is equal to accidents[0], lowest 3 regions tie for least accidents
		cout << "The " << region[0] << ", " << region[1] << ", and " << region[2] << " regions tied for the least accidents with " << accidents[0] << " accidents." << endl;
	}
	else if (accidents[1] == accidents[0]) {																		// if accidents[1] and accidents[0] are equal, they are the 2 lowest regions
		cout << "The " << region[0] << " and " << region[1] << " regions tied for least accidents with " << accidents[0] << " accidents." << endl;
	}
	else {																											// o/w accidents[0] is lowest accident region
		cout << "The " << region[0] << " region had the least accidents with " << accidents[0] << " accidents." << endl;
	}
}

// regex function for validating positive integer value
// parameters: input string to validate
bool validateInt(string stringToTest) {

	regex validUnsignedInt("(^[0-9]+[0-9]*$)");				// regex for positive integers of any size

	if (regex_match(stringToTest, validUnsignedInt)) {		// if input matches regex return true
		return true;
	}
	else {													//  o/w return false
		return false;
	}
}
