/*

Name: Stephen Gerkin
Date: 02/05/2019
Lesson 5 Program 2
Program Title:
	Distance Fallen Calculator
Program Description:
	This program displays how far an object will fall every second for 1-10 seconds

*/
#include <iostream>
using namespace std;

const double g = 9.8;	// constant for gravity

// function prototypes
double fallingDistance(int);

// main body
int main() {

	// welcome msg
	cout << "Welcome to the Distance Fallen Per Second Calculator.\n"
		"This program will tell you how far an object has travelled for every second." << endl << endl;

	// loop to display falling distances for seconds 1-10
	for (int i = 1; i <= 10; i++) {
		cout << "After " << i << " second";
		if (i != 1) {
			cout << "s";
		}
		cout << ", an object will have fallen " << fallingDistance(i) << " meters." << endl;
	}

	// exit msg
	cout << endl << "Thanks for taking the time to fall through this information!" << endl;

	system("pause");
	return 0;
}

// function to calculate distance
// parameters: time in seconds
double fallingDistance(int t) {

	double d = (1.0 / 2) * g * pow(t, 2);	// formula for calculating distance travelled
	return d;
}