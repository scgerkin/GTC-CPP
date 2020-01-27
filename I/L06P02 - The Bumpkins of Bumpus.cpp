/*

Name: Stephen Gerkin
Date: 02/08/2019
Lesson 6 Program 2
Program Title:
	The Bumpkins of Bumpus
Program Description:
	Program to read input file, process data, and write output file
	Reads in Bumpkin statistics and determines how to traverse Bumpus and its
	many doors

*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// function prototypes
double standardizeMeasurement(char, double);
string determineTravelMethod(double, double);
void readFile(ifstream&,ofstream&);


/*
* Main function body
*/
int main() {
	ifstream inputFile("bumpkins.in");		// init and open input file
	ofstream outputFile("bumpkins.out");	// init and open output file
	
	// determine if input file read success
	if (inputFile) {
		// print success message
		cout << "Input file found.\n" << "Writing data to \"bumpkins.out\"\n";
	}
	else {
		// print error message, end program
		cout << "Error opening file \"bumpkins.in\"\n" << "Please check that "
             << "file is in correct location and re-open the program.\n";
		system("pause");
		return 0;
	}

	// process input file and write to output file
	readFile(inputFile, outputFile);

	// print process complete
	cout << "Processing complete.\n";

	// close input and output files
	inputFile.close();
	outputFile.close();

	cout << "Files closed successfully.\n";

	system("pause");
	return 0;
}

/*
* Name:
*	readFile
* Parameters:
*	inputFile	input file to read
*	outputFile	output file to write
* Return:
*	void
* Description:
*	Reads input file line by line and writes data to outputfile
*/
void readFile(ifstream& inputFile, ofstream& outputFile) {
	string 	bumpName;		// bumpkin name

	int 	bumpsToHelp,	// # of bumpkins to help
			doorsToCalc;	// # of doors to calculate for bumpkin

	double	bumpHeight,		// bumpkin height
			doorHeight;		// door height

	char	unit;			// unit input type

	// get # of bumpkins to help for loop
	inputFile >> bumpsToHelp;

	// outer for loop, repeats for each bumpkin to help
	for (int i = 1; i <= bumpsToHelp; i++) {
		inputFile >> bumpName;		// get bumpkin name
		inputFile >> doorsToCalc;	// get # doors to calc
		inputFile >> bumpHeight;	// get bumpkin height
		inputFile >> unit;			// get height measurement unit

		// convert bumpkin height to centimeter standard
		bumpHeight = standardizeMeasurement(unit, bumpHeight);

		// write bumpkin name to output file with line break
		outputFile << bumpName << endl;

		// inner for loop to get info for each door
		for (int j = 1; j <= doorsToCalc; j++) {
			inputFile >> doorHeight;	// get door height
			inputFile >> unit;			// get door height measurement unit

			// convert door height to centimeter standard
			doorHeight = standardizeMeasurement(unit, doorHeight);

			// print door way # to output file
			outputFile << "Doorway " << j << ": ";
			// print travel method to output file
			outputFile << determineTravelMethod(doorHeight, bumpHeight);
			// print line break to output file
			outputFile << endl;
		}
		
		// print line break between each bumpkin
		outputFile << endl;
	}
}

/*
* Name:
*	determineTravelMethod
* Parameters:
*	d	door height
*	b	bumpkin height
* Return:
*	string	travel method as string
* Description:
*	Determines travel method and returns it as a string
*/
string determineTravelMethod(double d, double b) {

	// conditionals for determining travel method
	// return travel method
	if (b*0.25 >= d) {
		return "Blocked";
	}
	else if (b*0.40 >= d) {
		return "Limbo";
	}
	else if (b*0.65 >= d) {
		return "Crawl";
	}
	else if (b*1.05 >= d) {
		return "Duck";
	}
	else if (b*1.25 >= d) {
		return "Walk";
	}
	else {
		return "Stilts";
	}
}

/*
* Name:
*	standardizeMeasurement
* Parameters:
*	unit	unit for measurement received from input file
*	value	measurement value to convert
* Return:
*	double	measurement as centimeters after conversion
* Description:
*	Converts any unit type to centimeters for standard calculations
*/
double standardizeMeasurement(char unit, double value) {

	// switch conditional for unit type
	switch (unit) {
	case 'y':			// if yard, convert to feet
		value *= 3.0;
	case 'f':			// if feet, convert to inches
		value *= 12.0;
	case 'i':			// if inches, convert to centimeter and break
		value *= 2.54;
		break;
	case 'm':			// if meters, convert to centimeter
		value *= 100.0;
	case 'c':			// if centimeter, do nothing
		break;
	}
	return value;		// return value
}