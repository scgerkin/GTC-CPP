/*

Name: Stephen Gerkin
Date: 02/02/2019
Lesson 4 Program 1
Program Title:
	Hotel Occupancy Calculator
Program Description:
	This program calculates the occupancy rate for a hotel after getting the top floor level,
	checks if the ground floor has rooms, rooms per individual floor, and # of rooms occupied per floor
	Skips 13th floor for common building practice
	Displays total rooms in hotel, total occupied, total vacant, and occupancy rate

*/

#include <iostream>
#include <iomanip>
#include <regex>
#include <string>
using namespace std;

// function prototypes
unsigned int
	getTopFloor(),								// get total floors
	getRoomsOnFloor(int),						// get rooms on floor
	getOccupiedRoomsOnFloor(int, unsigned int);	// get occupied rooms on floor
bool
	queryGroundFloorHasRooms(),					// check if ground floor has rooms
	validateYN(string),							// validate y/n entry
	validateInt(string);						// validate integer entry
void
	displayTotals(unsigned int, unsigned int);	// display final calculations

// main body
int main() {

	unsigned int
		topFloor,						// top floor # of hotel
		startFloor,						// starting point of floors with rooms, 1 if ground floor has rooms, 2 if not -- used in loop count
		roomsOnFloor,					// total rooms on a floor
		occupiedRoomsOnFloor,			// occupied rooms on a floor
		totalRoomsInHotel = 0,			// accumulator for total rooms in hotel, init as 0
		totalOccupiedRoomsInHotel = 0;	// accumulator for total occupied rooms in hotel, init as 0

	// entrance msg
	cout << "Welcome to the Hotel Occupancy Rate Calculator!\n" << endl
		<< "This program will help you calculate the occupancy of your hotel.\n" << endl;

	do {
		topFloor = getTopFloor();			// get # of floors in hotel

		startFloor = 1;						// set lowest floor with rooms to ground floor

		if (!queryGroundFloorHasRooms()) {	// query if ground floor has rooms
			startFloor += 1;				// if not, set lowest floor with rooms to 2
		}

		if (startFloor > topFloor) {						// if the user returns 1 floor with rooms
			cout << "\aThe hotel cannot have 0 rooms.\n";	// and also returns ground floor has no rooms
		}													// display error and loop again to get
	} while (startFloor > topFloor);						// total # of floors


	for (unsigned int i = startFloor; i <= topFloor; i++) {						// loop to get all user data
		if (i != 13) {															// skips 13th floor
			roomsOnFloor = getRoomsOnFloor(i);									// function to get total rooms on floor i
			totalRoomsInHotel += roomsOnFloor;									// accumulate all total rooms in hotel

			occupiedRoomsOnFloor = getOccupiedRoomsOnFloor(i, roomsOnFloor);	// call function to get total occupied rooms on floor i
			totalOccupiedRoomsInHotel += occupiedRoomsOnFloor;					// accumulate total all occupied rooms in hotel
		}
	}

	displayTotals(totalRoomsInHotel, totalOccupiedRoomsInHotel);		// call function to display results

	// exit msg
	cout << "\nThanks for using the Hotel Occupancy Rate Calculator!\n";
	cout << "We hope your stay was accomodating.\n" << endl;

	system("pause");
	return 0;
}

// function to get total floors in hotel
unsigned int getTopFloor() {

	string userInput;			// user input, allows checking with regex w/o causing exceptions
	unsigned int returnValue;	// user input as converted datatype

	// loop to get user input for total floors
	do {
		cout << "Please enter the top floor number of the hotel: ";
		cin >> userInput;
		cout << endl;

		if (!validateInt(userInput)) {		// display error if input was not a valid integer
			cout << "\aThat was not a valid number.\nPlease enter a positive integer.\n";
		}
		else if (stoul(userInput) == 0) {	// displays error if 0 returned by user
			cout << "\aThere cannot be 0 floors.\n";
		}
	} while (!validateInt(userInput) || stoul(userInput) == 0);	// loop while input not valid or user input is 0

	returnValue = stoul(userInput);		// convert user input to valid datatype
	return returnValue;					// return value
}

// function to get total rooms on a floor
// parameters: floor number
unsigned int getRoomsOnFloor(int floor) {

	string userInput;				// user input, allows checking with regex w/o causing exceptions
	unsigned int returnValue;		// user input as converted datatype

	// loop for input
	do {
		cout << "Please enter the total number of rooms on floor " << floor << ": ";
		cin >> userInput;

		if (!validateInt(userInput)) {				// if user does not input a valid integer, display error
			cout << "\n\aThat was not a valid number.\nPlease enter a positive integer.\n";
		}
		else if (stoul(userInput) < 10) {			// if user inputs a room # less than 10, display error
			cout << "\n\aThat was not a valid entry.\n"
				<< "All floors must have at least 10 rooms.\n";
		}
	} while (!validateInt(userInput) || stoul(userInput) < 10);		// loop if input is invalid or value is less than 10

	returnValue = stoul(userInput);		// convert input to datatype
	return returnValue;					// return value
}

// function to get occupied rooms on a floor
// parameters: floor number, maximum rooms allowed to be occupied
unsigned int getOccupiedRoomsOnFloor(int floor, unsigned int maxRooms) {

	string userInput;				// user input, allows checking with regex w/o causing exceptions
	unsigned int returnValue;		// user input as converted datatype

	// loop for input
	do {
		cout << "Please enter the number of occupied rooms for floor " << floor << ": ";
		cin >> userInput;
		cout << endl;

		if (!validateInt(userInput)) {				// if user does not input a valid integer, display error
			cout << "\aThat was not a valid number.\nPlease enter a positive integer.\n";
		}
		else if (stoul(userInput) > maxRooms) {		// if user inputs a number greater than total rooms on floor, display error
			cout << "\aThat was not a valid entry.\n"
				<< "There cannot be more occupied rooms than total rooms on the floor.\n";
		}
	} while (!validateInt(userInput) || stoul(userInput) > maxRooms);	// loops if input is invalid or user inputs occupied rooms greater than total rooms on floor

	returnValue = stoul(userInput);		// convert user input to datatype
	return returnValue;					// return value
}

// function to query if ground floor has rooms
bool queryGroundFloorHasRooms() {

	string userInput;		// user input

	cout << "Does the ground floor have any rooms (y/n)? ";

	// loop for y/n input
	do {
		cin >> userInput;
		cout << endl;
	} while (!validateYN(userInput));	// loops until user enters valid y/n response

	if (userInput == "Y" || userInput == "y") {		// if user enters y, return true
		return true;
	}
	else {											// o/w return false
		return false;
	}
}

// function to validate y/n response using regex
// parameters: input string to validate
bool validateYN(string stringToTest) {

	regex validYN("([Y|N|y|n])");		// regex to check against

	if (regex_match(stringToTest, validYN)) {		// return true if valid input
		return true;
	}
	else {											// o/w display error message and return false
		cout << "\aSorry, that was not a recognized entry.\n";
		cout << "Please enter 'y' or 'n': ";
		return false;
	}
}

// regex function for validating integer input
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

// function to display final output to user
// parameters: total rooms in hotel, total occupied rooms in hotel
void displayTotals(unsigned int totalRooms, unsigned int occupiedRooms) {
	cout << "The total number of rooms in the hotel is " << totalRooms << endl;						// display total rooms in hotel
	cout << "The number of occupied rooms in the hotel is " << occupiedRooms << endl;				// display total occupied rooms in hotel
	cout << "The number of vacant rooms is " << totalRooms - occupiedRooms << endl;					// display total vacant rooms in hotel
	cout << fixed << showpoint << setprecision(2);													// set precision for % display to ###.##%
	cout << "The occupancy rate is " << (((1.0*occupiedRooms) / totalRooms)*100.0) << "%." << endl;	// display occupancy rate, one integer value multiplied by 1.0 for proper calculation
}