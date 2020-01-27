/*
Name: Stephen Gerkin
Date: 03/15/2019
Lesson 10 Program 1
Program Title:
    VendCo Inc. Vending Machines
Program Description:
    Program functions as a vending machine
    Displays the drinks sold and money earned after done vending
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

// global vars
const int MAX_DRINKS = 20;      // max drinks allowed in a machine

// structure declarations
struct Drink {                  // Drink structure:
    string name;                // name of the drink
    double cost;                // cost of drink
    int quantity;               // quantity of drink in a machine
    int sold;                   // number of drink sold
};

struct Machine {                // Machine structure:
    string fileLoc;             // file location for input of drink values
    Drink drink[MAX_DRINKS];    // Drink array for drinks in the machine
    int num_drinks;             // Number of Drinks in the machine
    double total_money;         // Total money in the machine
    bool vending;               // Boolean flag for currently active machine
};

// function prototypes
void
// init function
initMachine(Machine&),                  // initializes a machine with drinks

// display functions
displayMenu(Machine),                   // displays the machine menu
dispenseDrink(string),                  // displays drink dispensed
displaySoldOut(string),                 // displays sold out drink
dispenseChange(double),                 // displays change dispensed
refundMoney(double),                    // displays money refunded
displayStats(Machine);                  // displays the machine stats

// get functions    
int
getSelection(Machine);                  // gets menu selection
double
getMoney();                             // gets money

// calc function
double
determineChange(double, double);        // calculates change

bool
// validation function
regMatch(string, string);               // validates input

bool
// workhorse function
vend(Machine&);                         // runs a machine

/*
* Main Body:
*   Declares new Machine structures and then sends them to the vend function
*   for user interaction. Displays the machine stats once a machine is done
*   being used
*/
int main() {
    // declare a new machine
    Machine sodaMachine;
    // init the file location of the machine drink values
    sodaMachine.fileLoc = "SodaList.csv";

    // welcome msg
    cout << "Welcome to VendCo Inc. Vending Machines." << endl
        << "Serving up all the best drinks money can buy!" << endl
        << "Currently only selling Sodas, but we hope to add more soon!" << endl
        << endl;

    // init machine
    initMachine(sodaMachine);

    // vend drinks
    while (sodaMachine.vending) {
        sodaMachine.vending = vend(sodaMachine);
    };

    system("cls");

    // display the statistics for the machine
    displayStats(sodaMachine);

    // exit msg
    cout << endl
        << endl
        << "Thanks for using VendCo Inc. Vending Machines!" << endl
        << endl << endl;

    // terminate program
    system("pause");
    return 0;
}

/*
* Name:
*   initMachine
* Parameters:
*   active  reference to the Machine to be initialized
* Return:
*   none
* Description:
*   Function initializes a new machine using a file. Location of file should be
*   stored in the Machine structure's fileLoc variable before calling this
*   function. This function allows scalability for easily creating machines that
*   dispense different drinks
*/
void initMachine(Machine &active) {
    // open file for input
    ifstream drinkFile(active.fileLoc);

    // temp var for reading input
    string readValue;

    // var for machine.drink index
    int i = 0;

    do {
        // read in line from file
        getline(drinkFile, readValue);

        // drink name is first value of string read until delimiter
        active.drink[i].name =
            readValue.substr(0, readValue.find_first_of(","));

        // erase string up to and including delimiter
        readValue.erase(0, readValue.find_first_of(",") + 1);

        // drink cost is now first value of string read
        active.drink[i].cost =
            stod(readValue.substr(0, readValue.find_first_of(",")));

        // erase string up to and including delimiter
        readValue.erase(0, readValue.find_first_of(",") + 1);

        // what is left of the string read is drink quantity
        active.drink[i].quantity = stoi(readValue);

        // init number of drinks sold as 0 for index
        active.drink[i].sold = 0;

        // increment number of drinks read in by file
        i++;
    } while (!drinkFile.eof()); // do until end of file

    // close file
    drinkFile.close();
    // init the rest of the machine
    active.num_drinks = i;
    active.total_money = 0;
    active.vending = true;
}

/*
* Name:
*   displayMenu
* Parameters:
*   active      Machine structure currently being used
* Return:
*   none
* Description:
*   displays the drink selections of the current machine
*/
void displayMenu(Machine active) {
    cout << fixed << setprecision(2);
    cout << "Current drink selections:" << endl;

    for (int i = 0; i < active.num_drinks; i++) {
        cout << i + 1 << ": " << setw(10) << left << active.drink[i].name << "\t" << setw(4) << active.drink[i].cost;

        if (active.drink[i].quantity == 0) {
            cout << "\tSOLD OUT";
        }
        cout << endl;
    }

    cout << active.num_drinks + 1 << ": Exit" << endl << endl;
}

/*
* Name:
*   dispenseDrink
* Parameters:
*   drinkName   name of drink to be dispensed
* Return:
*   none
* Description:
*   displays what drink is dispensed
*/
void dispenseDrink(string drinkName) {
    system("cls");
    cout << drinkName << " dispensed." << endl;
}

/*
* Name:
*   displaySoldOut
* Parameters:
*   name        name of drink that is sold out
* Return:
*   none
* Description:
*   informs user that selected drink is sold out
*/
void displaySoldOut(string name) {
    system("cls");
    cout << name << " is sold out." << endl;
}

/*
* Name:
*   dispenseChange
* Parameters:
*   change  change to dispense
* Return:
*   none
* Description
*   displays change dispensed
*/
void dispenseChange(double change) {
    cout << endl << "Dispensing change: $" << change << "." << endl << endl;
}

/*
* Name:
*   refundMoney
* Parameters:
*   money   amount of money to refund
* Return:
*   none
* Description:
*   displays amount of money to be refunded to user
*/
void refundMoney(double money) {
    cout << "You did not insert enough money." << endl;
    cout << "This machine is refunding: $" << money << endl;
}

/*
* Name:
*   displayStats
* Parameters:
*   active      Machine structure to display the stats of
* Return:
*   none
* Description:
*   displays the machine statistics after it's done being used
*/
void displayStats(Machine active) {

    system("cls");

    // begin display with header
    cout << "DRINKS SOLD" << endl << endl;

    // loop for each drink
    for (int i = 0; i < active.num_drinks; i++) {
        if (active.drink[i].sold == 0) { // if no drink sold, end iteration
            continue;
        }
        else {  // otherwise print the name of the drink and the # sold
            cout << setw(10) << left << active.drink[i].name << "\t"
                << setw(4) << active.drink[i].sold << endl;
        }
    }
    // display total money earned
    cout << endl << "Total sales: $" << fixed << setprecision(2)
        << active.total_money << endl;
}

/*
* Name:
*   getSelection
* Parameters:
*   active      Machine that is actively being used
* Return:
*   int         user selection as integer
* Description:
*   gets money from user and returns it as an int
*/
int getSelection(Machine active) {
    string userIn;                              // var for user input
    string validEntry = "(^[0-9]+[0-9]*$)";     // regex pattern for validation
    int selection;                              // user input as integer

    cout << "Make your drink selection: ";
    getline(cin, userIn);

    if (!regMatch(userIn, validEntry)) {
        // invalid input
        cout << "\aInvalid Entry" << endl;
        // recur
        return getSelection(active);
    }
    else {
        selection = stoi(userIn);
    }

    if (selection > (active.num_drinks + 1) || selection < 1) {
        // invalid selection
        cout << "\aInvalid Entry" << endl;
        // recur
        return getSelection(active);
    }
    else {
        return selection;
    }
}

/*
* Name:
*   getMoney
* Parameters:
*   none
* Return:
*   double      money inserted by user
* Description:
*   gets money from user, only allows values from 0.01 to 1.00
*/
double getMoney() {
    string userIn;                                  // var for user input

    string validEntry =                          // regex pattern for validation
        "^([0]?[.][0-9][0-9]?)|([1][.]?[0]?[0]?)$"; // only allows entry 0.01 to
                                                    // 1.00, allows lazy entry
                                                    // eg .##, #, #.#, #.##

    cout << "Please insert money: $";
    getline(cin, userIn);

    if (!regMatch(userIn, validEntry)) {
        cout << "\aInvalid Entry" << endl
            << "This machine cannot accept more than $1" << endl;

        // recur until good entry input
        return getMoney();
    }
    else {
        return stod(userIn);
    }
}

/*
* Name:
*   determineChange
* Parameters:
*   money   the money inserted into the machine
*   cost    the cost of a selected soda
* Return:
*   double  the change to be dispensed by the machine
* Description:
*   Function subtracts the cost of a soda from the money inserted and returns
*   that value
*/
double determineChange(double money, double cost) {
    return (money - cost);
}

/*
* Name:
*   regMatch
* Parameters:
*   input       string value to check
*   pattern     pattern to check against
* Return:
*   bool    t/f     if string matches, return true
* Description:
*   Function for validating input is of an accepted pattern
*   Case is set to insensitive
*/
bool regMatch(string input, string pattern) {
    regex regpattern(pattern, regex_constants::icase);

    if (regex_match(input, regpattern))
        return true;
    else
        return false;
}

/*
* Name:
*   vend
* Parameters:
*   active  Reference to Machine structure that is actively being used
* Return:
*   bool    t/f returns a boolean to the function that calls to determine if
*           the structure should be used again
* Description:
*   Workhorse of the program. Takes an initialized Machine structure and
*   interacts with it. Unless the user selects to exit the machine, it will
*   always return true
*   This function calls the I/O functions for a Machine and.
*/
bool vend(Machine &active) {
    double moneyIn = 0.00,      // var for money inserted
        changeOut = 0.00;    // var for change dispensed
    int selection;              // var for user selection

    // display menu
    displayMenu(active);

    // get drink selection
    selection = getSelection(active);

    // determine what to do with selection
    if (selection == active.num_drinks + 1) {
        // user selected exit
        return false;
    }
    else {
        // decrement selection for use as index
        selection--;
    }

    // determine if selection sold out
    if (active.drink[selection].quantity < 1) {
        displaySoldOut(active.drink[selection].name);
        return true;
    }

    // get money from user
    moneyIn = getMoney();


    // if not enough money, refund their money and end vending
    if (moneyIn < active.drink[selection].cost) {
        refundMoney(moneyIn);
        return true;
    }

    // increment money in machine by money inserted
    active.total_money += moneyIn;

    // determine change
    changeOut = determineChange(moneyIn, active.drink[selection].cost);

    // decrement money in machine by change
    active.total_money -= changeOut;

    // dispense drink
    dispenseDrink(active.drink[selection].name);

    // if there is change, dipense the change
    if (changeOut != 0) {
        dispenseChange(changeOut);
    }

    // decrement number of selected drink in machine
    active.drink[selection].quantity--;

    // increment number of selected drink sold
    active.drink[selection].sold++;

    // end vending
    return true;
}