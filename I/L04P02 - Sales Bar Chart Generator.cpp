/*

Name: Stephen Gerkin
Date: 02/02/2019
Lesson 4 Program 2
Program Title:
	Sales Bar Chart Generator
Program Description:
	Program reads input from "sales.dat" and displays on screen as a bar chart
	Writes the display to "results.dat"

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int main() {

	ifstream inputFile("sales.dat");		// define and open input file
	ofstream outputFile("results.dat");		// define and open output file

	const int DOLLAR_PER_STAR = 100;		// constant for dollar to star conversion

	int salesAmount;						// input variable, sales amount
	int storeNumber = 1;					// store number accumulator

	// welcome msg
	cout << "Welcome to the Sales Bar Chart tool.\n"
		<< "\nThis program will displays sales in the \"sales.dat\" file\n"
		<< "as a bar chart and write it to \"results.dat\"\n" << endl;

	// open chart msg
	cout << "SALES BAR CHART\n" << "(Each * = $" << DOLLAR_PER_STAR << ")\n";

	while (inputFile >> salesAmount) {									// read file while not EOF
		cout << "Store #" << setw(2) << storeNumber << ": ";			// display store # for each entry
		outputFile << "Store #" << setw(2) << storeNumber << ": ";		// write store # to output file

		for (int i = 1; i <= (salesAmount / DOLLAR_PER_STAR); i++) {	// for loop to print a '*' based on constant
			cout << "*";												// display '*' for each loop
			outputFile << "*";											// write '*' to output file for each loop
		}

		cout << endl;		// write new line
		outputFile << endl;	// write new line to file
		storeNumber++;		// increment store number
	}

	inputFile.close();		// close input file
	outputFile.close();		// close output file

	// exit msg
	cout << "\nThanks for using this program for all your charting needs.\n";

	system("pause");
	return 0;
}