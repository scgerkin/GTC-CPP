#include <iostream>
#include <iomanip>
#include "Patient.h"
#include "Procedure.h"
#include "InputValidation.h"

// function declarations
void patientCharges();
bool repeatProgram();

/**Main entry point for program.*/
int main() {
    while (true) {
        system("cls");
        patientCharges();
        if (!repeatProgram()) {
            break;
        }
    }
    return 0;
}

/** Demonstration function.
Demonstrates the Patient and Procedure classes by instantiating a Patient object
and an array of Procedure objects with sample data. Prints the objects to the
screen and calculates total charges for procedures then displays that.
*/
void patientCharges() {
    // instantiate a Patient object with sample data
    Patient patient("Alfred", "Matthew", "Yankovic",
                    "123 Street Rd.",
                    "Albuquerque", "NM", "11230",
                    "555-555-1234",
                    "Cindy-Lou Who",
                    "555-555-4321");
    // print patient to console
    patient.print();

    // initialize array of Procedure objects with sample data
    const int NUM_PROCEDURES = 3;
    Procedure procedures[NUM_PROCEDURES] {
        {"Physical Exam", "09/04/2019", "Dr. Irvine", 250.00},
        {"X-ray", "09/04/2019", "Dr. Jamison", 500.00},
        {"Blood test", "09/04/2019", "Dr. Smith",200.00}
    };

    // iterate over Procedure objects to print each and calculate total charges
    std::cout << "\nProcedures performed:\n\n";
    double totalProcedureCharge = 0;
    for (Procedure procedure : procedures) {
        procedure.print();
        std::cout << "\n";
        totalProcedureCharge += procedure.getCharge();
    }
    
    // display calculated total charges
    std::cout << "Total charge: $" << std::setprecision(2) << std::showpoint
        << std::fixed << totalProcedureCharge << std::endl;
}

/** Function to repeat program.
Displays prompt to user asking if they would like to repeat the program.
Waits for input consisting of "y" or "n" (case insensitive).

@return True if user wants to repeat program.
*/
bool repeatProgram() {
    std::string userInput;

    while (true) { // loop until valid y/n entry
        std::cout << "\n\nDo you want to run the program again? (y/n)\n>> ";
        std::getline(std::cin, userInput);

        if (validYN(userInput)) {
            break; // end loop
        }
        else {
            std::cout << "That was not a recognized entry.\n"
                << "Please enter only 'y' or 'n'" << std::endl;
        }
    }
    return userInput == "Y" || userInput == "y";
}