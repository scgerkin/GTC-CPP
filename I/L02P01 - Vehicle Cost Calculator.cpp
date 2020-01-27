/*

Name: Stephen Gerkin
Date: 01/18/2019
Lesson 2 Program 1
Program Title:
	Vehicle Cost Calculator
Program Description:
	This program asks the user to enter a number of expenses for maintaining
	a car. It then displays the total monthly expenses and the annual expenses.

*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	// declare local variables
	float userInput,		// variable for user input
		expenses;			// variable for running total of expenses

  // program begin message
	cout << "Welcome to the Vehicle Cost Calculator" << endl;
	cout << "This program will calculate your monthly and annual costs of maintaining a vehicle." << endl << endl;

	// get loan payment, set to expenses
	cout << "Enter the monthly loan payment: ";
	cin >> userInput;
	expenses = userInput;

	// get insurance payment, add to expenses
	cout << "Enter the monthly insurance payment: ";
	cin >> userInput;
	expenses += userInput;

	// get gas cost, add to expenses
	cout << "Enter the amount spent this month on gas: ";
	cin >> userInput;
	expenses += userInput;

	// get oil cost, add to expenses
	cout << "Enter the estimated monthly cost of oil: ";
	cin >> userInput;
	expenses += userInput;

	// get tire cost, add to expenses
	cout << "Enter the estimated monthly cost of tires: ";
	cin >> userInput;
	expenses += userInput;

	// get maintenance cost, add to expenses
	cout << "Enter the amount spent on all other maintenance: ";
	cin >> userInput;
	expenses += userInput;

	// display total monthly expenses and annual expenses
	cout << endl;
	cout << fixed << setprecision(2);		// set precision for cents display
	cout << "The monthly cost of your vehicle is $" << expenses << endl;
	cout << "The annual cost of your vehicle is $" << expenses * 12 << endl << endl;

	// exit message
	cout << "Thanks for using this program" << endl;
	cout << "Take \"car\" and remember to buckle up!" << endl;

	system("pause");
	return 0;
}