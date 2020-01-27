#include <string>
#include <iostream>
#include <iomanip>
#include <regex>
#include "CustomerDataDemo.h"
#include "NegativePurchase.h"

/**
 * \brief Starts the demonstration of the PreferredCustomer class.
 * Creates a new class and has the user modify the sales purchase amounts to
 * display the discount levels.
 * Continues to allow modifying of sales while user desires.
 */
void startDemo() {
    PreferredCustomer customer;
    constructCustomer(customer);
    bool keepModifyingSales = true;
    while (keepModifyingSales) {
        modifySales(customer);
        keepModifyingSales = checkModifySalesAgain();
    }
}

/**
 * \brief Constructs a PreferredCustomer object from user input.
 * \param customer The object to construct.
 */
void constructCustomer(PreferredCustomer &customer) {
    customer.setLastName(getStringField("last name"));
    customer.setFirstName(getStringField("first name"));
    customer.setAddress(getStringField("street address"));
    customer.setCity(getStringField("city"));
    customer.setState(getStringField("state"));
    customer.setZip(getStringField("zip code"));
    customer.setPhone(getStringField("phone number"));
    customer.setCustomerNumber(getCustomerNumber());
    customer.setMailingList(getMailingListStatus());
}

/**
 * \brief Gets a string for a specified field from the user.
 * \param fieldName The field the user should enter data for. 
 * \return The user input as a string.
 */
std::string getStringField(const std::string &fieldName) {
    std::string input;
    std::cout << "Enter the customer " << fieldName << "\n>> ";
    std::getline(std::cin, input);
    std::cout << std::endl;
    return input;
}

/**
 * \brief Gets an integer value from the user to use as a customer ID number.
 * \return User input as integer.
 */
int getCustomerNumber() {
    while (true) {
        std::string input = getStringField("ID number");

        std::regex pattern("(^[0-9]+[0-9]*$)");

        if (std::regex_match(input, pattern)) {
            return std::stoi(input);
        }

        std::cout << "Please enter a valid integer value only." << std::endl;
    }
}

/**
 * \brief Gets a boolean value from the user determining if a customer is on the
 * mailing list.
 * \return User input as boolean.
 */
bool getMailingListStatus() {
    std::string input;

    while (true) {
        std::cout << "Add this customer to the mailing list? (y/n)\n>> ";
        std::getline(std::cin, input);

        std::regex pattern("([Y|N])", std::regex_constants::icase);
        if (std::regex_match(input, pattern)) {
            break;
        }
        else {
            std::cout << "That was not a recognized entry.\n"
                      << "Please enter only 'y' or 'n'" << std::endl;
        }
    }
    return input == "Y" || input == "y";
}

/**
 * \brief Gets a sales amount from the user to modify the PreferredCustomer
 * object with.
 * Provides functionality to show the current sales and discount level.
 * \param customer The customer object we're working on.
 */
void modifySales(PreferredCustomer &customer) {
    std::string input;
    displayPurchasesAmount(customer);
    while (true) {
        std::cout << "Enter new purchases amount:\n>> ";
        std::getline(std::cin, input);
        std::cout << std::endl;

        // regex for dollar entry, allowing comma delimiter
        // does not allow signed values
        // only allows 2 decimal spots
        std::regex pattern("^[0-9]{1,3}(?:,?[0-9]{3})*(?:.[0-9]{2})?$");

        if (std::regex_match(input, pattern)) {
            try {
                customer.setPurchasesAmount(std::stoi(input));
                break;
            }
            catch (NegativePurchase &) {
                // continue
            }
        }
        else {
            std::cout << "Invalid entry." << std::endl
                      << "Please enter a valid amount." << std::endl;
        }
    }
    std::cout << "Purchases updated..." << std::endl;
    displayPurchasesAmount(customer);
}

/**
 * \brief Displays the current sales amount and discount level for the customer.
 * \param customer The object we want to display the information for.
 */
void displayPurchasesAmount(const PreferredCustomer &customer) {
    std::cout << std::endl;
    std::cout << "Current purchase amount: $" << std::setprecision(2)
              << std::fixed << customer.getPurchasesAmount() << std::endl
              << std::setprecision(0)
              << "Current discount: " << customer.getDiscountLevel() * 100
              << "%" << std::endl;
}

/**
 * \brief Determines if the user wants to modify the sales amount again.
 * \return True if the user wants to continue modifying sales amount.
 */
bool checkModifySalesAgain() {
    std::string input;

    std::cout << "Modify sales again? (y/n):\n>> ";

    while (true) {
        std::getline(std::cin, input);

        std::regex pattern("([Y|N])", std::regex_constants::icase);
        if (std::regex_match(input, pattern)) {
            break;
        }
        else {
            std::cout << "That was not a recognized entry.\n"
                      << "Please enter only 'y' or 'n'" << std::endl;
        }
    }
    return input == "Y" || input == "y";
}
