/*
Name: Stephen Gerkin
Date: 03/15/2019
Leson 10 Program 2
Program Title:
    Speaker's Bureau
Program Description:
    Program uses an array of a structure to store information about speakers
    Allows for entering new speakers, editing individual records, and entire
    records
*/

#include <iostream>
#include <iomanip>
#include "validate.h"               // custom regex validator
// includes <string> and <regex>
using namespace std;

// structure declarations
struct Bureau {                     // Bureau structure for program
    string name;                    // name field
    string phoneNo;                 // phone field
    string topic;                   // topic field
    double fee;                     // speaker fee field
};

enum MenuType { HOME, NEW, EDIT };  // enumerator for menu types

struct Menu {                       // menu structure for program
    vector<string> dispStr;         // menu items
    MenuType type;                  // type of menu
};


//function prototypes
Menu
constructMenu(MenuType);                // menu structure constructor

void
// display functions
displayMenu(Menu),                      // display menu
displayAllRecords(bool, Bureau*, int),  // display all records
displaySingleRecord(Bureau*, int),      // display single record
// edit functions
editExisting(Bureau*, int, Menu),       // edit existing record
editEntire(Bureau*, int);               // edit entire existing record

// get functions
string
getString(string, bool);                // get field values
double
getFee(bool);                           // get fee as double
int
getMenuSelection(Menu),                 // get menu selection
getID(int);                             // get ID
bool
getNewRecord(Bureau*, int, Menu);       // get a totally new record

void
invalidEntry(),                         // display function for bad input
confirmExit();                          // exit confirmation function

/*
* Main function body
*   This function starts the bulk of the program and then loops it until
*   the user selects exit in another function.
*/
int main() {
    // declare/init menus used by the program
    Menu home = constructMenu(HOME);
    Menu newEntry = constructMenu(NEW);
    Menu editEntry = constructMenu(EDIT);

    Bureau speakerList[20]; // Bureau array used by program
    int numSpeakers = 0;    // accumulator for filled array

    int menuSelection;  // var for menu selection

    //welcome msg
    cout << "Welcome to the speaker's bureau organizing tool!" << endl
        << "This program will help you keep track of all the necessary"
        << " information." << endl
        << "Please be aware this program only supports a list of 20 speakers."
        << endl;

    // loop for menu selection
    do {
        // display the home menu
        displayMenu(home);

        // get selection
        menuSelection = getMenuSelection(home);

        // determine selection
        switch (menuSelection) {
        case 0: // exit
            confirmExit();
            break;
        case 1: // display all records, name only
            displayAllRecords(false, speakerList, numSpeakers);
            break;
        case 2: // display all records, detailed
            displayAllRecords(true, speakerList, numSpeakers);
            break;
        case 3: // get new record
            // call get new record function, if new entry is saved, increment
            // accumulator
            if (getNewRecord(speakerList, numSpeakers, newEntry)) {
                numSpeakers++;
            }
            break;
        case 4: // edit existing record
            editExisting(speakerList, numSpeakers, editEntry);
            break;
        }
        // loop forever until user selects exit which will exit the program
    } while (true);
}

/*
* Name:
*   constructMenu
* Parameters
*   NAME    MenuType enumerator that determines what menu is being initialized
* Return:
*   Menu    initialized menu
* Description:
*   Function creates a Menu structure with appropriate menu item and returns it
*/
Menu constructMenu(MenuType NAME) {
    Menu temp;  // var for Menu structure that is being created

    // initialize the vector index 0 with Exit program
    temp.dispStr.push_back("Exit Program)");
    // initialize the name of the menu as the parameter entered
    temp.type = NAME;

    // determine and initialize
    if (NAME == HOME) {
        temp.dispStr.push_back("Display all records (name only)");
        temp.dispStr.push_back("Display all records (detailed)");
        temp.dispStr.push_back("Enter new record");
        temp.dispStr.push_back("Edit existing record");
    }
    if (NAME == NEW) {
        temp.dispStr.push_back("Save");
        temp.dispStr.push_back("Discard");
    }
    if (NAME == EDIT) {
        temp.dispStr.push_back("Name");
        temp.dispStr.push_back("Phone number");
        temp.dispStr.push_back("Topic");
        temp.dispStr.push_back("Fee");
        temp.dispStr.push_back("Entire record");
    }

    return temp;
}

/*
* Name:
*   displayMenu
* Parameters:
*   name    Menu structure that is to be displayed
* Return:
*   none
* Description:
*   Displays the menu that is currently relevant to the user
*/
void displayMenu(Menu name) {
    cout << endl;

    // display menu items
    for (unsigned int i = 1; i < name.dispStr.size(); i++) {
        cout << uppercase << hex << i << nouppercase << ": " << name.dispStr[i] << endl;
    }
    // display exit menu item
    cout << endl
        << "0: Exit Program" << endl
        << endl
        << "Enter your selection: ";
}

/*
* Name:
*   displayAllRecords
* Parameters:
*   detailed        boolean value for displaying detailed record list
*   *list           Pointer to Bureau array that is to be displayed
*   listSize        Array value of greatest index used by the array
* Return:
*   none
* Description:
*   Function displays all the records currently entered into the program
*   Displays a detailed record if the user selected detailed record
*/
void displayAllRecords(bool detailed, Bureau *list, int listSize) {
    int maxNameLength = 0;   // var for formatting output of name field
    int maxTopicLength = 0;  // var for formatting output of topic field

    system("cls");

    // if no records, display msg and exit function
    if (listSize <= 0) {
        cout << "There currently no records to display." << endl << endl;
        return;
    }

    cout << fixed << left;

    // determine length of longest name
    for (int i = 0; i < listSize; i++) {
        int temp;
        temp = list[i].name.length();
        if (temp > maxNameLength) {
            maxNameLength = temp;
        }
    }

    // determine length of longest topic
    for (int i = 0; i < listSize; i++) {
        int temp;
        temp = list[i].topic.length();
        if (temp > maxTopicLength) {
            maxTopicLength = temp;
        }
    }


    // for formatting purposes, the length of fields should be at least 7
    if (maxNameLength < 7) {
        maxNameLength = 7;
    }
    if (maxTopicLength < 7) {
        maxTopicLength = 7;
    }

    // add some space for the formatting
    maxNameLength += 2;
    maxTopicLength += 2;

    // display header
    cout << setw(5) << "ID" << setw(maxNameLength) << "Name";
    // if detailed is true, display the detailed records
    if (detailed) {
        cout << setw(14) << "Phone" << setw(maxTopicLength) << "Topic" << setw(7) << "Fee";
    }
    cout << endl;

    // display the records
    for (int i = 0; i < listSize; i++) {
        cout << setw(5) << i + 1 << setw(maxNameLength) << list[i].name;
        if (detailed) {
            cout << setw(14) << list[i].phoneNo << setw(maxTopicLength)
                << list[i].topic << setw(2) << setprecision(2) << "$" << list[i].fee;
        }
        cout << endl;
    }
    cout << endl;
}

/*
* Name:
*   displaySingleRecord
* Parameters:
*   *list       Pointer to array values to be displayed
*   index       index value of the array to be displayed
* Return:
*   none
* Description:
*   Function displays the values of a single index of an array of Bureaus to be
*   displayed. Taken in this way to allow display from the actual active arrays
*   and also from the temp arrays used by various functions.
*/
void displaySingleRecord(Bureau *list, int index) {
    string idNum;       // var for ID number to display
    int nameLength;     // var for formatting output of name field
    int topicLength;    // var for formatting output of topic field

    // if displaying a new entry, set display to new
    if (index - 1 < 0) {
        idNum = "NEW";
    }
    // otherwise set the display to the index value (+1 because index display
    // starts at 1, not 0
    else {
        idNum = to_string(index + 1);
    }

    // set formatting size to size of fields
    nameLength = list[index].name.length();
    topicLength = list[index].topic.length();

    // fields should be at least 7 characters for best formatting
    if (nameLength < 7) {
        nameLength = 7;
    }

    if (topicLength < 7) {
        topicLength = 7;
    }

    // add some space
    nameLength += 2;
    topicLength += 2;

    // display the record with formatting and header
    cout << setw(5) << "ID" << setw(nameLength) << "Name" << setw(14)
        << "Phone" << setw(topicLength) << "Topic" << setw(7) << "Fee"
        << endl;
    cout << setw(5) << idNum << setw(nameLength) << list[index].name
        << setw(14) << list[index].phoneNo << setw(topicLength)
        << list[index].topic << setw(2) << setprecision(2) << "$"
        << list[index].fee << endl;
}

/*
* Name:
*   editExisting
* Parameters:
*   *speakerList    pointer to array of Bureau to be edited
*   numSpeakers     total number of active indices in the array
*   editEntry       Menu structure for editing existing records
* Return:
*   none
* Description:
*   Function takes a pointer to an array of the Bureau structure to edit
*   Gets the ID value for the index to be edited
*   Changes the values in the array to user entry
*/
void editExisting(Bureau *speakerList, int numSpeakers, Menu editEntry) {
    int selectionID;    // var for ID selection from user
    int selectionMenu;  // var for menu selection from user

    system("cls");

    // if the array is empty, display such and exit function
    if (numSpeakers <= 0) {
        cout << "There are currently no records to edit." << endl;
        return;
    }
    // display all the records that can be edited
    displayAllRecords(true, speakerList, numSpeakers);

    // get ID number to be edited
    cout << "Enter the ID # you wish to edit: ";
    selectionID = getID(numSpeakers);

    // loop for menu selection
    do {
        system("cls");
        // display the record selected for editing
        displaySingleRecord(speakerList, (selectionID - 1));

        // display menu for editing
        displayMenu(editEntry);

        // get selection
        selectionMenu = getMenuSelection(editEntry);

        // decide what to do based on selection
        switch (selectionMenu) {
        case 0: // exit program
            confirmExit();
            break;
        case 1: // edit name 
            speakerList[selectionID - 1].name = getString("name", true);
            break;
        case 2: // edit phone
            speakerList[selectionID - 1].phoneNo = getString("phone number", true);
            break;
        case 3: // edit topic
            speakerList[selectionID - 1].topic = getString("topic", true);
            break;
        case 4: // edit fee
            speakerList[selectionID - 1].fee = getFee(true);
            break;
        case 5: // edit the entire structure
            editEntire(speakerList, (selectionID - 1));
            break;
        }
        // loop if user selected exit without confirmation
    } while (selectionMenu == 0);
}

/*
* Name:
*   editEntire
* Parameters:
*   *speakerList    pointer to array of Bureau to be edited
*   index           index of array to be edited
* Return:
*   none
* Description:
*   Function takes pointer to array to be edited, gets input for each variable
*   of the structure as a temporary value
*   Confirms if the entry was correct and should be saved
*   If entry was correct, values in temporary array are put into original array
*/
void editEntire(Bureau *speakerList, int index) {
    Bureau temp[1];     // temp Bureau array for entry
    string confirmEdit; // var for confirming entry was correct

    system("cls");

    // get values for the temp array
    temp[0].name = getString("name", false);
    temp[0].phoneNo = getString("phone number", false);
    temp[0].topic = getString("topic", false);
    temp[0].fee = getFee(false);

    // loop for menu selection
    do {
        system("cls");

        // display entered info
        displaySingleRecord(temp, 0);

        // display confirmation information was entered correctly
        cout << endl << "Is this information correct? (y/n): ";
        getline(cin, confirmEdit);

        // validate input as y/n entry
        if (!regex_yn(confirmEdit)) {
            invalidEntry();
            continue;
        }
        // loop if confirm entry input was not a valid Y/N response
    } while (!regex_yn(confirmEdit));

    // determine if entry is correct and should be saved
    // if Y was not entered, information is discarded
    if (confirmEdit == "Y" || confirmEdit == "y") {   //save
        speakerList[index].name = temp[0].name;
        speakerList[index].phoneNo = temp[0].phoneNo;
        speakerList[index].topic = temp[0].topic;
        speakerList[index].fee = temp[0].fee;
    }
}

/*
* Name:
*   getString
* Parameters:
*   field       the name of the field the function is retrieving (for display)
*   existing    boolean value for if the function is getting a value for an
*               already existing element in an array
* Return:
*   string      the input from the user
* Description:
*   Function gets input from user, validates that it is not empty, then returns
*   the input
*/
string getString(string field, bool existing) {
    string input;

    // display what is being asked for
    cout << "Enter the ";
    // if the function is changing an already existing value, add some clarity
    if (existing) {
        cout << "new ";
    }
    cout << field << ": ";

    // get input
    getline(cin, input);

    // check if input was empty, if it was, recur
    if (input.empty()) {
        cout << "\aFields cannot be blank!" << endl;
        return getString(field, existing);
    }

    // once function gets to here, input is confirmed valid and is returned
    return input;
}

/*
* Name:
*   getFee
* Parameters
*   existing    boolean value for if the function is getting a value for an
*               already existing element in an array
* Description:
*   Function gets input from user, validates it as an unsigned floating point
*   number for currency, then returns the input as a double
*/
double getFee(bool existing) {
    string input;   // var for user input

    // display what is being asked for
    cout << "Enter the";
    // if the function is changing an already existing value, add some clarity
    if (existing) {
        cout << " new";
    }
    cout << " hourly fee: $";

    // get input
    getline(cin, input);

    // validate input as an unsigned floating point number, if not recur
    if (!regex_u_float(input)) {
        invalidEntry();
        return getFee(existing);
    }

    // once function gets to here, input is confirmed valid and is returned
    return stod(input);
}

/*
* Name:
*   getMenuSelection
* Parameters:
*   Menu    currentMenu     Menu structure of the menu currently being used
* Return:
*   int     menu selection entered by user as integer
* Description:
*   Function gets input from user, validates the entry, then checks that the
*   entry is an actual menu item. Returns the selection as an integer
*/
int getMenuSelection(Menu currentMenu) {
    string input;   // var for user input

    // get input
    getline(cin, input);

    // validate input is an integer, if not recur
    if (!regex_hex(input)) {
        invalidEntry();
        return getMenuSelection(currentMenu);
    }

    // validate input is an available menu selection, if not recur
    if (stoul(input) >= currentMenu.dispStr.size()) {
        cout << "\aThat is not a menu option." << endl;
        return getMenuSelection(currentMenu);
    }

    // once function gets to here, input is confirmed valid and is returned
    return stoi(input);
}

/*
* Name:
*   getID
* Paramenters:
*   maxID       the greatest value of active indices in the array
* Return:
*   int     Returns input as integer value
* Description:
*   Function asks user to input an integer, validates the entry, then checks
*   to make sure the value is used by the array. Returns the ID that should be
*   worked on
*/
int getID(int maxID) {
    string input;   // var for user input

    // get input
    getline(cin, input);

    // validate input is an integer, if not recur
    if (!regex_int(input)) {
        invalidEntry();
        return getID(maxID);
    }

    // if input is not a valid, active ID, recur
    if ((stoi(input) - 1) >= maxID) {
        cout << "ID does not exist." << endl;
        return getID(maxID);
    }

    // once function gets to here, input is confirmed valid and is returned
    return stoi(input);
}

/*
* Name:
*   getNewRecord
* Parameters:
*   *speakerList    pointer to array of Bureau values to add to
*   index           Number of active indices in Bureau array
*   confirmNew      Menu structure for confirming new entry
* Return:
*   bool    t/f     If after a new entry is input and confirmed, return true
* Description:
*   Function takes a pointer to an array of the Bureau structure to add to
*   Gets input for each variable of the structure as a temporary value
*   Confirms if information entered was correct and should be saved
*   If information confirmed, returns a true value
*   If information discarded, returns a false value
*/
bool getNewRecord(Bureau *speakerList, int index, Menu confirmNew) {
    Bureau temp[1];     // temp Bureau array for entry
    int menuSelection;  // var for menu selection after entry is entered

    system("cls");

    // get values for the temp array
    temp[0].name = getString("name", false);
    temp[0].phoneNo = getString("phone number", false);
    temp[0].topic = getString("topic", false);
    temp[0].fee = getFee(false);

    // loop for menu selection
    do {
        system("cls");

        // display entered info
        displaySingleRecord(temp, 0);

        // display menu and get selection
        displayMenu(confirmNew);
        menuSelection = getMenuSelection(confirmNew);

        system("cls");

        // if exit, confirm
        if (menuSelection == 0) {
            confirmExit();
        }
        // loop if user selected exit and decided not confirm
    } while (menuSelection == 0);

    // do menu selection and return if a new entry was entered or not
    if (menuSelection == 1) {   //save
        speakerList[index].name = temp[0].name;
        speakerList[index].phoneNo = temp[0].phoneNo;
        speakerList[index].topic = temp[0].topic;
        speakerList[index].fee = temp[0].fee;
        return true;
    }
    else {  // discard
        return false;
    }
}

/*
* Name:
*   invalidEntry
* Parameters:
*   none
* Return:
*   none
* Description:
*   Function displays output that an entry was invalid. Called by any function
*   that uses regex from validate.h for validation.
*/
void invalidEntry() {
    cout << "\aInvalid Entry" << endl;
}

/*
* Name:
*   confirmExit
* Parameters:
*   none
* Return:
*   none
* Description:
*   Function asks for confirmation that the user wants to exit the program
*   If confirmed, this function terminates the program
*/
void confirmExit() {
    string input;   // temp var for input

    // display confirmation
    cout << endl << endl << "Are you sure you want to exit?" << endl
        << "Any unsaved data will be lost. (y/n): ";

    // get choice
    getline(cin, input);

    // validate y/n input, if not valid recur
    if (!regex_yn(input)) {
        invalidEntry();
        return confirmExit();
    }

    // if input y, terminate program
    if (input == "Y" || input == "y") {
        cout << endl << endl << "Exiting program" << endl << endl;
        system("pause");
        exit(0);
    }

    // if program gets to here, user does not want to exit
    return;
}