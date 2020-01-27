/*

Name: Stephen Gerkin
Date: 01/18/2019
Lesson 2 Program 2
Program Title:
	Seconds Conversion Tool
Program Description:
	This program takes seconds as input from the user,
	converts the seconds into days, hours, and minutes
	then displays the result to the user. It loops until
	a negative value is entered.
	
*/

#include <iostream>
using namespace std;

// global constants for calculations
const int	SEC_PER_MIN = 60,
SEC_PER_HR = SEC_PER_MIN * 60,
SEC_PER_DAY = SEC_PER_HR * 24;

// ref point for testing:
// 90'061 seconds = 1 day, 1 hour, 1 minute, 1 second
// 180'122 seconds is 2 days, 2 hours, 2 minutes, 2 seconds

int main() {
	// declare local variables for holding time conversions
	long long int	seconds = 0;		// initialize as 0 for loop to run, use long long for greatest range of seconds possible
	
	unsigned int	days,				// these values will never be less than 0, so use unsigned for greater range
					hours,
					minutes;

	// beginning message
	cout << "Welcome to the seconds conversion tool." << endl;
	cout << "This program will convert seconds to days, hours, or minutes" << endl;
	cout << "Enter a negative value at any time to end the program." << endl << endl;

	// program will loop until a negative value is entered
	while (seconds >= 0) {

		// get seconds input
		cout << "Enter the number of seconds you want to convert: ";
		cin >> seconds;
		cout << endl;

		// break loop for negative value
		if (seconds < 0) {
			break;
		}

		// start of out message 
		cout << "That is";

		// calculate days if seconds >= 86'400
		if (seconds >= SEC_PER_DAY) {										// if seconds converts to days, find number of days
			days = (seconds - (seconds % SEC_PER_DAY)) / SEC_PER_DAY;		// take remainder of seconds after day conversion, convert to days by subtracting
																			// remainder and dividing by seconds in day
			seconds = seconds % SEC_PER_DAY;								// set seconds to remainder of seconds after day conversion
			
			if (days > 1) {
				cout << " " << days << " days";								// if more than one day, send out total days + "days"
			} else {														// otherwise send out "day"
				cout << " " << days << " day";
			}
		}

		if (seconds >= SEC_PER_HR) {										// if seconds left converts to hours, find number hours
			hours = (seconds - (seconds % SEC_PER_HR)) / SEC_PER_HR;		// use same calc method as with days
			seconds = seconds % SEC_PER_HR;									// set seconds to remainder of seconds left after hour conversion
			
			if (hours > 1) {
				cout << " " << hours << " hours";							// if more than one hour, send out total hours + "hours"
			} else {														// otherwise send out "hour"
				cout << " " << hours << " hour";
			}
		}

		if (seconds >= SEC_PER_MIN) {										// if seconds left converts to minutes, find number of minutes
			minutes = (seconds - (seconds % SEC_PER_MIN)) / SEC_PER_MIN;	// same method as above
			seconds = seconds % SEC_PER_MIN;								// set seconds to remainder of seconds left after minute conversion
			
			if (minutes > 1) {
				cout << " " << minutes << " minutes";						// if more than one minute, send out total minutes + "minutes"
			} else {														// otherwise, send out "minute"
				cout << " " << minutes << " minute";
			}
		}

		if (seconds > 1) {													// if seconds remain, send out number of seconds + "seconds"
			cout << " " << seconds << " seconds";
		} else if (seconds > 0) {											// otherwise, if only 1 second remaining, send out "second"
			cout << " " << seconds << " second";
		}

		cout << ".\n" << endl;												// end out statement with "."
	}

	cout << "Program terminating." << endl;									// exit message
	cout << "Thanks for your time...!" << endl;

	system("pause");
	return 0;
}