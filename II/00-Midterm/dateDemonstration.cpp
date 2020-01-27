#include "dateDemonstration.h"
#include "test_Date.h"

/**
 * Demonstrates the Date class by creating a Date object and allowing the user
 * to manipulate it in various ways. Also allows the user to view the status of
 * the unit tests.
 */
void demonstrateDateClass() {
    // create a Date to demonstrate and use for modification
    Date date;
    displayDate(date);
    // display menu and get choice
    MENU_SELECTION selection = displayMainMenu();

    while (selection != EXIT) {
        switch (selection) {
            case CHANGE_DATE:
                changeDate(date);
                break;
            case CHANGE_FORMAT:
                changeDateFormat(date);
                break;
            case INCREMENT_DATE:
                date++;
                break;
            case DECREMENT_DATE:
                date--;
                break;
            case DAYS_BETWEEN:
                demonstrateDaysBetweenDates(date);
                break;
            case PERFORM_MATH:
                demonstrateSubtractionOperator(date);
                break;
            case UNIT_TESTS:
                std::cout << "\n\n PERFORMING UNIT TESTS ... \n\n";
                test_Date td;
                break;
        }
        displayDate(date);
        std::cout << "\n";
        selection = displayMainMenu();
    }
}

/**
 * Displays the main menu for demonstrating a Date object.
 * @return The MENU_SELECTION selection selected by the selector.
 */
MENU_SELECTION displayMainMenu() {
    std::cout << "\n"
              << "1. Change Date\n"
              << "2. Change Date Format\n"
              << "3. Increment Date\n"
              << "4. Decrement Date\n"
              << "5. Check days between another date\n"
              << "6. Subtract Dates to determine days between\n"
              << "7. Show the status of unit testing for Date.\n"
              << "8. EXIT\n\n";

    int selection = getMenuSelection(8);

    switch (selection) {
        case 1: return CHANGE_DATE;
        case 2: return CHANGE_FORMAT;
        case 3: return INCREMENT_DATE;
        case 4: return DECREMENT_DATE;
        case 5: return DAYS_BETWEEN;
        case 6: return PERFORM_MATH;
        case 7: return UNIT_TESTS;
        case 8: return EXIT;
    }
}

/**
 * Gets a menu selection from the user in the form of an integer option.
 * This mostly validates that the user entered a correct choice.
 * @param maxSelections The maximum number of selections offered to the user.
 * @return An integer value representing the selection choice.
 */
int getMenuSelection(int maxSelections) {
    int minSelections = 1;
    int userSelection = -1;
    // try to get input until we get a valid selection
    while (true) {
        std::string userInput;

        std::cout << "Make a selection ...\n" << ">> ";
        std::getline(std::cin, userInput);

        try {
            userSelection = stoi(userInput);
            if (userSelection > maxSelections || userSelection < minSelections) {
                throw std::invalid_argument("Not a valid selection.");
            }
            // if we get here, good input, end the loop
            break;
        }
        catch (const std::invalid_argument &ex) {
            std::cout << "\nThat was not a valid selection.\n";
        }
    }

    std::cout << "\n";
    return userSelection;
}

/**
 * Displays a Date object and current formatting style to the user.
 * @param date The date to display.
 */
void displayDate(const Date &date) {
    std::cout << "\n\n";
    std::cout << "The current date is: " << date << "\n"
              << "The display format is: " << date.getDateStringFormatDisplayString()
              << "\n";
}

/**
 * Allows a user to change a date object by inputting new values for a date.
 * @param date The date we want to change.
 */
void changeDate(Date &date) {
    while (true) {
        try {
            std::cout << "Enter a date value, enter 'q' to exit:\n>> ";
            std::string input;
            std::getline(std::cin, input);
            if (input[0] == 'q') {
                break;
            }
            std::stringstream ss;
            ss << input;
            ss >> date;
            std::cin >> date;
            std::cin.ignore(1, '\n');
            break;
        }
        catch (const std::invalid_argument &ex) {
            handleBadDateInput(date);
        }
    }

}

/**
 * Displays correct input format options to the user.
 * @param date The Date the user is currently attempting to change.
 */
void handleBadDateInput(const Date &date) {
    auto validEntryFormats = createValidInputStringDisplays(date);

    std::cout << "Sorry, that input was not recognized.\n"
              << "Please make sure your input is in one of these forms:\n";
    for (std::string format : validEntryFormats) {
        std::cout << format << "\t";
    }
    std::cout << "\n";
}

/**
 * Creates a list of valid input formats for a Date object.
 * @param date The Date the user is currently attempting to change.
 * @return A list of valid format string examples for the current Date object.
 */
std::vector<std::string> createValidInputStringDisplays(const Date &date) {
    // create an empty container for storing our possible displays
    std::vector<std::string> displayStrings;

    // determine what order input should be entered
    bool usFormat = date.getDateStringFormat() == Date::US_SHORT
                    || date.getDateStringFormat() == Date::US_LONG;

    for (char delimiter : date.getValidDelimiters()) {
        std::stringstream ss;
        std::string display;
        if (usFormat) {
            ss << "MM" << delimiter << "DD" << delimiter << "YYYY";
        }
        else {
            ss << "DD" << delimiter << "MM" << delimiter << "YYYY";
        }
        ss >> display;
        displayStrings.emplace_back(display);
    }

    return displayStrings;
}

/**
 * Displays a menu for changing the current date format of the Date object.
 * The date format will be changed based on selections after this function is
 * finished.
 * @param date The date we wish to change the format for.
 */
void changeDateFormat(Date &date) {
    displayCurrentDateFormat(date);
    displayChangeDateFormatMenu(date);
}

/**
 * Displays the current date format of the Date object.
 * @param date The Date object we're working with.
 */
void displayCurrentDateFormat(const Date &date) {
    std::cout << "Your current format is: "
              << date.getDateStringFormatDisplayString() << "\n"
              << "That looks like this: " << date << "\n\n";
}

/**
 * Displays the possible format options and gets user input to change the format
 * to.
 * @param date The Date object we're working with.
 */
void displayChangeDateFormatMenu(Date &date) {
    // create a temp copy so we can iterate over the formats
    Date tempCopy(date);

    // display the options
    for (int i = 0; i < Date::LAST; i++) {
        tempCopy.setDateStringFormat(static_cast<Date::DATE_STRING_FORMAT>(i));
        std::cout << i+1 << ". Format: " << tempCopy.getDateStringFormatDisplayString()
                  << " looks like " << tempCopy << "\n";
    }

    // get a selection and set it
    int selection = getMenuSelection(Date::LAST);
    date.setDateStringFormat(static_cast<Date::DATE_STRING_FORMAT>(selection - 1));
}

/**
 * Demonstrates the function to calculate the number of days between two dates.
 * The current date we're working with is copied to the first date value to have
 * a starting point but can be changed without changing the actual value inside
 * the Date object given to this function.
 * @param date The current date we're working with.
 */
void demonstrateDaysBetweenDates(const Date &date) {
    // make a copy of the current date we're working with in case the user wants
    // to use different date ranges
    Date first(date);
    Date second(date);

    std::cout << "Do you want to use the current date " << first << "?\n"
              << "1. Yes\n"
              << "2. No\n";

    switch(getMenuSelection(2)) {
        case 2: // no, change first date
            std::cout << "What is the first date?\n";
            changeDate(first);
            // cascade and get second date
        case 1:
            std::cout << "What is the second date?\n";
            changeDate(second);
            break;
    }

    std::cout << "\n\n";
    std::cout << "There are " << Date::daysBetween(first, second)
              << " days between " << first << " and " << second << "\n";
}

/**
 * Demonstrates the subtraction operator for two dates. If the first date used
 * is after the second date used, it'll display how many days until the second
 * date. Otherwise it'll display how many days it has been since.
 * The Date object given to this function is not modified.
 * @param date The current date we're working with.
 */
void demonstrateSubtractionOperator(const Date &date) {
    // make a copy of the current date we're working with in case the user wants
    // to use different date ranges
    Date first(date);
    Date second(date);

    std::cout << "Do you want to use the current date " << first << "?\n"
              << "1. Yes\n"
              << "2. No\n";

    switch(getMenuSelection(2)) {
        case 2: // no, change first date
            std::cout << "What is the first date?\n";
            changeDate(first);
            // cascade and get second date
        case 1:
            std::cout << "What is the second date?\n";
            changeDate(second);
            break;
    }

    int daysBetween = first - second;

    std::cout << "\n\n";

    if (daysBetween == 0) {
        std::cout << "Those are the same date!\n";
    }
    else if (daysBetween < 0) {
        std::cout << "On " << first << " it will be " << abs(daysBetween)
                  << " days until " << second << "\n";
    }
    else {
        std::cout << "On " << first << " it has been " << daysBetween
                  << " days since " << second << "\n";
    }
}

