/*

Name: Stephen Gerkin
Date: 01/22/2019
Lesson 3 Program 1
Program Title:
	Serendipity Booksellers Rewards calculator
Program Description:
	This program asks a user how many books they've purchased in a month and informs them of how many reward points they've earned.

*/

#include <iostream>
using namespace std;


int main() {

	int	booksPurchased = 0,
		pointsEarned = 0;

	// entrance message
	cout << "Welcome to the Serendipity Booksellers Rewards Club calculator.\n";
	cout << "This program will let you know how many points you've earned based\n";
	cout << "on the amount of books you've purchased this month.\n";
	cout << endl << "Enter a negative number at any time to exit the program.\n" << endl;

	// while loop runs until negative value entered
	while (booksPurchased >= 0) {

		cout << "Enter the number of books purchased this month: ";
		cin >> booksPurchased;

		if (booksPurchased < 0) {
			break;
		}
		else if (booksPurchased == 0) {
			pointsEarned = 0;
		}
		else if (booksPurchased == 1) {
			pointsEarned = 5;
		}
		else if (booksPurchased == 2) {
			pointsEarned = 15;
		}
		else if (booksPurchased == 3) {
			pointsEarned = 30;
		}
		else {
			pointsEarned = 60;
		}

		cout << "You earned " << pointsEarned << " points.\n" << endl;
	}

	// exit message
	cout << endl << "Thanks for using the program. Remember: Reading is FUNdamental!\n";

	system("pause");
	return 0;
}