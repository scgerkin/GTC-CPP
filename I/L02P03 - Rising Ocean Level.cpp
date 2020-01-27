/*

Name: Stephen Gerkin
Date: 01/18/2019
Lesson 2 Program 3
Program Title:
	Rising Ocean Level
Program Description:
	This program displays a table that shows the level of water rising in millimeters per year.
	Constants can be changed to update current year, # of years to display, and the rate at which the water
	is predicted to rise.

*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	// initialize constants
	const int	START_YR = 2019,		// current year
				YRS_TO_DISP = 25;		// # of years to display in table
	const float	MM_PER_YR = 1.5;		// mm water risen per year

	// program start message
	cout << "Welcome to the Rising Ocean Level program." << endl;
	cout << "The ocean's water level is currently rising at about 1.5 millimeters per year." << endl;
	cout << "The following table shows the amount of change over the next " << YRS_TO_DISP << " years.\n" << endl;

	cout << " ______ __________" << endl;					// open table formatting
	cout << "| Year | mm Risen |" << endl;


	for (int i = 1; i <= YRS_TO_DISP; i++)					// run loop for number of years to display
	{
		cout << "|______|__________|" << endl;				// table formatting
		cout << "|      |          |" << endl;
		cout << fixed << showpoint << setprecision(2);		// set precision for mm display formatting
		cout << "| " << START_YR + i << " | " << setw(8) << i * MM_PER_YR << " |" << endl;		// information to be displayed
	}

	cout << "|______|__________|\n" << endl;		// close table formatting

	cout << "Water you doing to help stem the tide of global warming?" << endl;
	
	system("pause");
	return 0;
}