/*

Name: Stephen Gerkin
Date: 03/01/2019
Midterm Project
Program Title:
    Hospital Charges
Program Description:
    Program gets patient information from a user, displays the information
    entered, then confirms if it should be written to file
    If that is confirmed, the patient name and total charges are written to file

*/
#include <iostream>
#include <string>
#include <fstream>
#include <regex>    
#include <sstream>  
#include <iomanip>  

using namespace std;

// declare global constants for regex values to check against
const string VALID_UNSIGNED_INT = "(^[0-9]+[0-9]*$)";
const string VALID_UNSIGNED_CURRENCY = "^[0-9]*(?:.[0-9]{2})?$";
const string VALID_NAME = "^[a-z\\-\\.]{1,15}(?:,\\s|\\s)[a-z\\-\\.]{1,15}";

// declare global constant: file name for save file
const string FILENAME = "PatientCharges.txt";


// function prototypes
bool                        // boolean function prototypes:
validInput(string, string), // checks if input is valid
checkInPt(),                // checks if patient is inpatient or outpatient
confirmAction(string);      // confirms an action to take

void                                    // void return functions:
writeToFile(ofstream&, string, double), // writes data to file
displayEnteredInfo(string),             // displays info entered by user
displayWelcomeMsg(),                    // displays welcome msg
displayEndMsg();                        // displays exit msg

int                         // integer return functions:
getDaysAdmitted();          // gets number of days pt is admitted

double                          // double return functions:
getAdmitRate(),                 // gets charge rate for inpatients
getUniversalCharges(string);    // gets charges universal to all patients

string                          // string return functions:
getPtName(),                    // gets 
numToStr(int),                  // converts integers to string
numToStr(double),               // converts double to string
getPtInfo(string&, double&);    // accumulates all patient info entry



/*
*   Main Method definition
*/
int main() {
    string ptInfo;      // variable for patient entry accumulated
    string ptName;      // variable for patient name
    double totalCharge; // variable for total charges for patient

    // output string for confirmation to save information to file
    string confirmWriteMsg;
    confirmWriteMsg = "Do you want to save this information to file?";

    // output string for confirmation to get another patient
    string confirmEnterNewPtMsg;
    confirmEnterNewPtMsg = "Do you want to enter information for another";
    confirmEnterNewPtMsg += " patient?";

    // open write file
    ofstream outFile(FILENAME);

    // display welcome message
    displayWelcomeMsg();

    do {
        // format for loop
        cout << endl;

        // get patient info
        ptInfo = getPtInfo(ptName, totalCharge);

        // display the information entered by the user
        displayEnteredInfo(ptInfo);

        // write information to file if user indicates confirm write
        if (confirmAction(confirmWriteMsg)) {
            writeToFile(outFile, ptName, totalCharge);
        }
    // loop while user confirms enter new patient
    } while (confirmAction(confirmEnterNewPtMsg));

    // close file
    outFile.close();

    // display exit message
    displayEndMsg();

    // terminate program
    system("pause");
    return 0;
}

/*
*   Name
*       validInput
*   Parameters:
*       stringToTest    string input by user
*       checkAgainst    regex pattern to check against
*   Return:
*       bool    true = valid entry, false = invalid
*   Description:
*       Function checks string input against regex patterns for valid input
*       Not case sensitive
*/
bool validInput(string stringToTest, string checkAgainst) {

    // sets regex check to case insensitive
    regex pattern(checkAgainst, regex_constants::icase);

    if (regex_match(stringToTest, pattern)) {
        return true;
    }
    else {

        return false;
    }
}

/*
*   Name:
*       checkInPt
*   Parameters:
*       none
*   Return:
*       bool    true if patient is in patient, false if not
*   Description:
*       Function gets inpatient or outpatient status of patient
*       Returns true if inpatient
*/
bool checkInPt() {
    string ptStatus;    // variable for user input; I for inpatient, O for out

    do {
        // get input
        cout << "Was this patient an inpatient or outpatient? (I/O): ";
        getline(cin, ptStatus);

        // clarify correct input if bad input entered
        if (!validInput(ptStatus, "I|O")) {
            cout << endl
                << "\aInvalid Entry!" << endl
                << "Please enter only \"I\" or \"O\"." << endl
                << endl;
        }
    // loop until valid input
    } while (!validInput(ptStatus, "I|O"));

    // if inpatient, return true
    if (ptStatus == "I" || ptStatus == "i") {
        return true;
    }
    else {
        return false;
    }
}

/*
*   Name:
*       confirmAction
*   Parameters:
*       outputMsg   Message to output to user for confirmation
*   Return:
*       bool    true = perform action in message
*   Description:
*       Function displays an action to take by the user based on string param
*       If user wants to perform the action, returns true
*/
bool confirmAction(string outputMsg) {
    string selection;   // variable for user input; yes/no selection

    do {
        // get input
        cout << outputMsg << " (Y/N): ";
        getline(cin, selection);

        // clarify correct input if bad input entered
        if (!validInput(selection, "Y|N")) {
            cout << endl
                << "\aInvalid Entry!" << endl
                << "Please enter only \"Y\" or \"N\"." << endl
                << endl;
        }
    // loop until valid input
    } while (!validInput(selection, "Y|N"));

    // if yes, return true o/w return false
    if (selection == "Y" || selection == "y") {
        return true;
    }
    else {
        return false;
    }
}

/*
*   Name:
*       writeToFile
*   Parameters:
*       file    pointer to file for writing
*       name    patient name to write
*       charge  total charges for patient
*   Return:
*       none
*   Description:
*       Writes patient name and charges to file
*/
void writeToFile(ofstream& file, string name, double charge) {
    file << "Patient name: " << name << endl
        << "Total charges: $" << fixed << setprecision(2) << charge << endl
        << endl;
}

/*
*   Name:
*       displayEnteredInfo
*   Parameters:
*       outputString    String value accumulated while patient info entered
*   Return:
*       none
*   Description:
*       Displays all patient information entered by user
*/
void displayEnteredInfo(string outputString) {
    cout << endl
        << endl
        << outputString
        << endl;
}

/*
*   Name:
*       displayWelcomeMsg
*   Parameters:
*       none
*   Return:
*       none
*   Description:
*       Displays the message to user indicating program start
*/
void displayWelcomeMsg() {
    cout << "Welcome to the Patient Information Data Entry Tool.\n"
        << endl
        << "Information entered here will be saved into \"" + FILENAME + "\""
        << endl;
}

/*
*   Name:
*       displayEndMsg
*   Parameters:
*       none
*   Return:
*       none
*   Description:
*       Displays the message to user indicating program termination
*/
void displayEndMsg() {
    cout << endl << "Program is complete.\n" << endl
        << "Patient names and charges have been saved to \"" + FILENAME + "\""
        << endl
        << "Please note, any data saved will be lost if this program\n"
        << "is run again without moving the file.\n" << endl;
}

/*
*   Name:
*       getDaysAdmitted
*   Parameters:
*       none
*   Return:
*       int     number of days patient was in hospital
*   Description:
*       Function gets number of days patient was in hospital
*       Validates entry for no negative numbers
*       Returns number of days as integer
*/
int getDaysAdmitted() {
    string daysAdmitted;    // variable for user input; number of days inpatient

    do {
        // get input
        cout << "Enter the number of days of admission: ";
        getline(cin, daysAdmitted);

        // clarify correct input if bad input entered
        if (!validInput(daysAdmitted, VALID_UNSIGNED_INT)) {
            cout << endl
                << "\aInvalid Entry!" << endl
                << "Days of admission cannot be less than 0." << endl
                << "Please enter only an positive integer value." << endl
                << endl;
        }
    // loop until valid input
    } while (!validInput(daysAdmitted, VALID_UNSIGNED_INT));

    // convert input to integer and return value
    return stoi(daysAdmitted);
}

/*
*   Name:
*       getAdmitRate
*   Parameters:
*       none
*   Return:
*       double  daily admission rate for patient
*   Description:
*       Function gets daily admission rate for patient from user
*       Validates for non-negative numbers
*       Only allows USD entry
*       If a decimal value is entered, can only be 2 digits
*       Returns entry as double
*/
double getAdmitRate() {
    string admitRate;   // variable for user input; daily charge for admission

    do {
        // get input
        cout << "Enter the daily admission charge rate: $";
        getline(cin, admitRate);

        // clarify correct input if bad input entered
        if (!validInput(admitRate, VALID_UNSIGNED_CURRENCY)) {
            cout << endl
                << "\aInvalid Entry!" << endl
                << "Daily charge rate cannot be less than 0." << endl
                << "Please enter only numbers in the form ###.##" << endl
                << endl;
        }
    // loop until valid input
    } while (!validInput(admitRate, VALID_UNSIGNED_CURRENCY));

    // convert input to double and return value
    return stod(admitRate);
}

double getUniversalCharges(string chargeName) {
    string chargeAmount;    // variable for user input; iteration charge amount

    do {
        // get input
        cout << "Enter the charge amount for " << chargeName << ": $";
        getline(cin, chargeAmount);

        // clarify correct input if bad input entered
        if (!validInput(chargeAmount, VALID_UNSIGNED_CURRENCY)) {
            cout << endl
                << "\aInvalid Entry!" << endl
                << "Daily charge rate cannot be less than 0." << endl
                << "Please enter only numbers in the form ###.##" << endl
                << endl;
        }
    // loop until valid input
    } while (!validInput(chargeAmount, VALID_UNSIGNED_CURRENCY));

    // convert value to double and return amount
    return stod(chargeAmount);
}

/*
*   Name:
*       getPtName
*   Parameters:
*       none
*   Return:
*       string  patient's name
*   Description:
*       Function gets patient's name from user
*       Validates only letter or common name symbols ("." or "-")
*       Only allows 15 characters per name position
*       Returns patient name as string
*/
string getPtName() {
    string ptName;  // variable for user input; pt's name

    do {
        // get input
        cout << "Enter the patient name: ";
        getline(cin, ptName);

        // clarify correct input if bad input entered
        if (!validInput(ptName, VALID_NAME)) {
            cout << endl
                << "\aInvalid Entry!" << endl
                << "Patient name should be in the following format:" << endl
                << "\"Lname, Fname\" or \"FName LName\"" << endl
                << "Each name cannot be more than 15 characters" << endl
                << "Only letters and punctuation are accepted." << endl
                << endl;
        }
    // loop until valid input
    } while (!validInput(ptName, VALID_NAME));

    // return patient name
    return ptName;
}

/*
*   Name:
*       numToStr
*   Parameters:
*       number  number to convert to string
*   Return:
*       string  number entered convereted to string value with formatting
*   Description:
*       Uses sstream to construct a string from number input for adding to
*       string accumulator in patient entry function
*/
string numToStr(double number) {
    stringstream returnString;

    returnString << fixed << setprecision(2) << number;

    return returnString.str();
}

/*
*   Name:
*       numToStr
*   Parameters:
*       number  number to convert to string
*   Return:
*       string  number entered convereted to string value
*   Description:
*       Uses sstream to construct a string from number input for adding to
*       string accumulator in patient entry function
*       Overload of function above
*/
string numToStr(int number) {
    stringstream returnString;

    returnString << number;

    return returnString.str();
}

/*
*   Name:
*       getPtInfo
*   Parameters:
*       ptName      patient's name as reference
*       totalCharge total charges as reference
*   Return:
*       ptInfoAccumulator   Display string of all entries from this function
*   Description:
*       function gets all patient charges
*       Adds all entry from user to a string which will be returned
*       This string can be displayed to confirm all entry was correct before
*       saving to file
*       Updates patient name and total charges reference variables for writing
*       just those values to the final file
*/
string getPtInfo(string& ptName, double& totalCharge) {
    int daysAdmitted;           // variable for days pt was in hospital
    double admitRate;           // variable for charge rate while admitted
    double admitCharge;         // total charges for admission
    double medCharge;           // medication charges
    double servCharge;          // service charges

    string ptInfoAccumulator;   // string accumulator collects input for later
                                // display, entry is concatenated to this string
                                // throughout function and then returned

    // init charges at 0
    totalCharge = 0;

    // get patient name
    ptName = getPtName();

    // start building entry output string
    ptInfoAccumulator = "Patient name: " + ptName + "\t\n";

    if (checkInPt()) {
        // get days admitted
        daysAdmitted = getDaysAdmitted();

        // get admission charge rate
        admitRate = getAdmitRate();

        // calc admission charge
        admitCharge = daysAdmitted * admitRate;

        // add to total charges
        totalCharge += admitCharge;

        // add inpatient info to entry output string
        ptInfoAccumulator += "Days admitted: " + numToStr(daysAdmitted) + "\n";
        ptInfoAccumulator += "Admit Rate: $" + numToStr(admitRate) + "\t\n";
        ptInfoAccumulator += "Admission charge: $" + numToStr(admitCharge)
            + "\n";
    }

    // get medication charges
    medCharge = getUniversalCharges("medication");

    // add to total
    totalCharge += medCharge;

    // get service charges
    servCharge = getUniversalCharges("services");

    // add to total
    totalCharge += servCharge;

    // finish building entry output string
    ptInfoAccumulator += "Medication charges: $" + numToStr(medCharge) + "\t\n";
    ptInfoAccumulator += "Services charge: $" + numToStr(servCharge) + "\t\n";
    ptInfoAccumulator += "Total charges: $" + numToStr(totalCharge) + "\t\n";

    // return entry string
    return ptInfoAccumulator;
}