/*

Name: Stephen Gerkin
Date: 02/08/2019
Lesson 6 Program 1
Program Title:
	Prime Number Calculator
Program Description:
	Program determines if a number is prime in a range
	Writes prime numbers to output file
	Optimized to run all numbers 1 to 1 million in about 5 seconds

*/
#include <iostream>
#include <fstream>
using namespace std;

//function prototype
bool isPrime(int);

/*
* Main function body
*/
int main() {
	
	const int 	MIN_RANGE = 1,		// start parameter for loop
				MAX_RANGE = 100;	// end parameter for loop

	// open and init output file
	ofstream outputFile("allprimes.dat");

	// display range to test
	cout << "Testing for prime numbers starting at " << MIN_RANGE << " and ending at " << MAX_RANGE << endl;

	// for loop passes number to check if prime
	// writes to output file if number is prime
	for (int i = MIN_RANGE; i <= MAX_RANGE; i++) {
		if (isPrime(i)) {
			outputFile << i << endl;
		}
	}

	// close output file
	outputFile.close();

	//
	cout << "All done!\n" << "All prime numbers written to \"allprimes.dat\"\n";

	system("pause");
	return 0;
}

/*
* Name:
*	isPrime
* Parameters:
*	num		number to check if prime
* Return:
*	bool	boolean
* Description:
*	determines if a number is prime, returns true if it is, false if not
*/
bool isPrime(int num) {
	if (num < 2) {
		return false;	// if number is less than 2, it is not prime
	}
	else if (num == 2 || num == 3 || num == 5 || num == 7) {
		return true;	// if number is 2, 3, 5, or 7, it is prime
	}
	else if (num % 2 == 0 || num % 3 == 0 || num % 5 == 0 || num % 7 == 0) {
		return false;	// if number is divisible by first 4 prime numbers, not prime
	}
	else {
		// for loop to test more additional divisors
		// stops at the square root of number to check + 1
		// no number is divisible by a its root + 1
		// if any number checked is a divisor of number to check, return false
		for (int i = 8; (i < (pow(num, 0.5) + 1)); i++) {
			if (num % i == 0) {
				return false;
			}
		}
	}
	return true; // if number passes all above, it is prime
}