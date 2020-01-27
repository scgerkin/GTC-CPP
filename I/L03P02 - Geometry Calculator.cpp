/*

Name: Stephen Gerkin
Date: 1/22/2019
Lesson 3 Program 2
Program Title:
	Geometry Calculator
Program Description:
	Program calculates and displays the area of a circle, square, or triangle based on user input

*/

#include <iostream>
#include <string>
#include <regex>

using namespace std;

// function prototypes
void calculateArea(int);
int getMenuSelection();
double getValue(int);
bool validateDouble(string);


int main() {

	// local variable for menu selection
	int menuSelection = 0;

	// entrance message
	cout << "Welcome to the Geometry Calculator\n" <<
			"We're here for all your Area Calculation Needs!" << endl;


	// display and get menu selection choice
	// call area calculation function
	// loop menu until 4 to quit is returned
	while (menuSelection != 4) {
		menuSelection = getMenuSelection();

		if (menuSelection != 4) {
			calculateArea(menuSelection);
		}
	}

	// exit message
	cout << endl << endl <<
			"Thanks for coming around to see us.\n" <<
			"I hope this program was hypotenuseful!\n" <<
			"Don't be a square and come back soon!\n" << endl;

	system("pause");
	return 0;

}

// function to display the program menu
// gets user choice and validates input
int getMenuSelection() {

	// local variables for menu selection
	string userInput = "";
	int menuSelection = 0;

	// regex only allows for entries listed on the menu
	regex validInt("[1-4]");

	// display menu, get user input, loop until valid entry selected
	while (!regex_match(userInput, validInt)) {

		cout << endl << endl <<
				"Here are your options...\n" <<
				"1. Calcluate the Area of a Circle\n" <<
				"2. Calcluate the Area of a Rectangle\n" <<
				"3. Calculate the Area of a Triangle\n" <<
				"4. Exit the program\n" <<
				endl <<
				"Enter your choice: ";
		cin >> userInput;

		// validate input, convert to int value
		// display error msg if invalid input received
		if (regex_match(userInput, validInt)) {
			menuSelection = stoi(userInput);
		}
		else {
			cout << "\a\n\nSorry, that was not a valid entry.\n" << endl;
		}
	}

	// return menuSelection as integer
	return menuSelection;
}


// function to get shape dimensions, calculate area, and display results
void calculateArea(int userSelection) {

	// local variables and constant for pi
	const double PI = 3.14159;
	double radius, base, height, area;
	string shapeType = "";

	// determine shape type, get dimensions, and calculate area
	if (userSelection == 1) {
		shapeType = "circle";
		radius = getValue(0);
		area = PI * radius*radius;
	}
	else if (userSelection == 2) {
		shapeType = "rectangle";
		base = getValue(1);
		height = getValue(2);
		area = base * height;
	}
	else {
		shapeType = "triangle";
		base = getValue(1);
		height = getValue(2);
		area = base * height * 0.5;
	}

	// display the shape type and area
	cout << endl <<  "The area of the " << shapeType << " is " << area << endl << endl;

}


// gets a number value from user and returns it to the area calculation function after validating input
double getValue(int iteration) {
	
	// local variables for function input, output, and validation
	string valueIn = "";
	double valueOut = 0;
	bool validInput = false;
	

	// line clear for clarity
	cout << endl;

	// get the user entry for shape dimensions and validate input
	// loop until entry is valid
	while (!validInput) {
		if (iteration == 0) {
			cout << "Enter the length of the radius: ";
			cin >> valueIn;
			validInput = validateDouble(valueIn);
		}
		else if (iteration == 1) {
			cout << "Enter the length of the base: ";
			cin >> valueIn;
			validInput = validateDouble(valueIn);
		}
		else {
			cout << "Enter the length of the height: ";
			cin >> valueIn;
			validInput = validateDouble(valueIn);
		}
	}
	
	// convert user string input to double data type and return it
	valueOut = stod(valueIn);
	return valueOut;

}

// validates that the user entered a valid number
bool validateDouble(string stringToTest) {

	// regex value allows for scientific notation
	// does not allow negative values
	regex validDouble("([[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");

	if (regex_match(stringToTest, validDouble)) {
		return true;
	}
	else {
		cout << "\n\aSorry, that was not a valid entry!\n";
		return false;
	}

}