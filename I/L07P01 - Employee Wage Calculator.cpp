/*

Name: Stephen Gerkin
Date: 02/08/2019
Lesson 7 Program 1
Program Title:
	Employee Wage Calculator
Program Description:
	Program to intake hours worked and pay rate for employees
	Stores in array
	Calculates wages and displays information

*/
#include <iostream>
#include <string>
#include <regex>
using namespace std;

// function prototypes
bool
	validatePosInt(string),
	validatePosDouble(string);

int
	getHoursWorked(int);

double
	getPayRate(int),
	calcWages(int, double);

/*
* Main function body
*/
int main() {

	const int	ARRAY_SIZE = 7;			// constant for array size

	long int 	empID[ARRAY_SIZE]	{5658845,		// array for emp id
									4520125,		// init array with employee ids
									7895122,
									8777541,
									8451277,
									1302850,
									7580489};
					
	int			hours[ARRAY_SIZE];		// array for hours
				
	double		payRate[ARRAY_SIZE],	// array for pay rate
				wages[ARRAY_SIZE];		// array for wages

	// welcome msg
	cout << "Welcome to the Employee Wage Calculator!\n" <<
			"This program calculates the weekly wages for an employee.\n" << endl;

	// get hours, payrate, and wages for each employee
	for (int i = 0; i < ARRAY_SIZE - 1; i++) {
		hours[i] = getHoursWorked(empID[i]);
		payRate[i] = getPayRate(empID[i]);
		cout << endl;
		wages[i] = calcWages(hours[i], payRate[i]);
	}

	// display employee ID and wage info for all indices of array
	for (int i = 0; i < ARRAY_SIZE - 1; i++) {
		cout << "Emp ID: " << empID[i] << " Wages: $" << wages[i] << endl;
	}

	cout << endl;

	// exit msg
	cout << "Thanks for using the program.\n" << endl;

	system("pause");
	return 0;
}

/*
* Name:
*	getPayRate
* Parameters:
*	empID	employee ID number
* Return:
*	int		hours worked
* Description:
*	gets hours worked for employee, does not allow value under 0
*/
int getHoursWorked(int empID) {
	string userInput;		// user input string
	int returnValue;		// user input return value as int

	do {
		cout << "Enter the number of hours for employee ID " << empID << ": ";
		cin >> userInput;

		if (!validatePosInt(userInput)) {
			cout << "That was not a valid entry.\n"
				<< "Please enter a positive integer.\n";
		}
	} while (!validatePosInt(userInput));

	// convert and return input
	returnValue = stoi(userInput);
	return returnValue;
}

/*
* Name:
*	getPayRate
* Parameters:
*	empID	employee ID number
* Return:
*	double	pay rate 
* Description:
*	gets pay rate for employee, does not allow for values under MIN_RATE
*/
double getPayRate(int empID) {
	const double	MIN_RATE = 15.00;	// minimum hourly pay rate
	string			userInput;			// user input string
	double			returnValue;		// user input return value as double
	
	do {
		cout << "Enter the pay rate for employee ID " << empID << ": ";
		cin >> userInput;

		if (!validatePosDouble(userInput) || stod(userInput) < MIN_RATE) {
			cout << "That was not a valid entry.\n"
				<< "Pay rate must be at least $15.00\n";
		}
	} while (!validatePosDouble(userInput) || stod(userInput) < MIN_RATE);

	// convert and return input
	returnValue = stod(userInput);
	return returnValue;
}
/*
* Name:
*	calcWages
* Parameters:
*	hours		hours worked
*	payRate		employee pay rate
* Return:
*	double		wage for pay period
* Description:
*	calculates wages and returns value
*/
double calcWages(int hours, double payRate) {
	double wages = hours * payRate;
	return wages;
}

/*
* Name:
*	validatePosDouble
* Parameters:
*	stringToTest	input string to check against regex
* Return:
*	bool	bolean for valid input
* Description:
*	checks strings against regex for valid positive double
*/
bool validatePosDouble(string stringToTest) {
	regex validPosDouble("([0-9]+([.][0-9]*)?|[.][0-9]+)");

	if (regex_match(stringToTest, validPosDouble)) {
		return true;
	}
	else {
		return false;
	}
}

/*
* Name:
*	validatePosInt
* Parameters:
*	stringToTest	input string to check against regex
* Return:
*	bool	bolean for valid input
* Description:
*	checks strings against regex for valid positive integers
*/
bool validatePosInt(string stringToTest) {
	regex validPosInt("(^[0-9]+[0-9]*$)");

	if (regex_match(stringToTest, validPosInt)) {
		return true;
	}
	else {
		return false;
	}
}