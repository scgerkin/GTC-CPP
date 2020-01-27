#include "Date.h"

#include <string>
#include <map>
#include <ctime>
#include <iostream>
#include <chrono>
#include <algorithm>

/**
 * No argument constructor creates an object with the current local Date.
 * This is accomplished using the now() static method to get the system clock.
 * The default formatting style is set to US_SHORT.
 */
Date::Date() noexcept
    : Date(now())
    {}

/**
 * Full argument constructor. Consider default.
 * Takes integer values for a Date object to construct.
 * Values should be passed in descending order of magnitude (YY/MM/DD) to avoid
 * confusion between various date formatting options.
 * Sets the string formatting for the date by provided parameter.
 * @param year int value for year.
 * @param month int value for month, must be between 1 and 12.
 * @param day int value for day, must be between 1 and max days in month.
 * @param format the specified format in which the string representation of Date
 * should be created.
 * @throws std::out_of_range exception if month is not valid or day is not valid
 * given a specified month or negative value entered for year.
 */
Date::Date(int year, int month, int day, Date::DATE_STRING_FORMAT format) {
    setDate(year, month, day);
    this->dateStringFormat = format;

    // set default delimiters
    validDelimiters.insert('/');
    validDelimiters.insert('.');
    validDelimiters.insert('-');
}

/**
 * Constructor without DATE_STRING_FORMAT specified.
 * Sets the format to US_SHORT by default.
 * Takes integer values for a Date object to construct.
 * Values should be passed in descending order of magnitude (YY/MM/DD) to avoid
 * confusion between various date formatting options.
 * @param year int value for year.
 * @param month int value for month, must be between 1 and 12.
 * @param day int value for day, must be between 1 and max days in month.
 * @throws std::out_of_range exception if month is not valid or day is not valid
 * given a specified month.
 */
Date::Date(int year, int month, int day) : Date(year, month, day, US_SHORT){}

/**
 * Copy constructor.
 * Default implementation is verbose here in case implementation needs changes.
 * @param obj Date object to copy.
 */
Date::Date(const Date &obj) noexcept {
    this->year = obj.getYear();
    this->month = obj.getMonth();
    this->day = obj.getDay();
    this->dateStringFormat = obj.getDateStringFormat();
    this->validDelimiters = obj.getValidDelimiters();
}

/**
 * Setter to change/set a new value for the date.
 * Values should be passed in descending order of magnitude (YY/MM/DD) to avoid
 * confusion between various date formatting options.
 *
 * If any field is invalid, the values for year and month will not be changed
 * from original values.
 * For example, let's say *this Date is 07/18/2018.
 * The input given to change the date is yyyy = 1999 mm = 03 dd = 32
 * This will throw an out_of_range exception because day cannot be 32
 *
 * To make sure we don't now have a date of 03/18/1999, before the exception is
 * thrown, each value is reset to what it was before being changed so the values
 * in *this will still be
 * year = 2018
 * month = 07
 * day = 18
 *
 * @param yyyy int value for year.
 * @param mm int value for month, must be between 1 and 12.
 * @param dd int value for day, must be between 1 and max days in month.
 * @throws std::out_of_range exception if month is not valid or day is not valid
 * given a specified month or year is less than 0.
 */
void Date::setDate(int yyyy, int mm, int dd) {
    int currentYear = this->getYear();
    int currentMonth = this->getMonth();


    if (yyyy < 0) {
        std::string exMsg = "Invalid Year value: " + std::to_string(yyyy) +
                            ". This class does not currently support BCE years.";
        throw std::out_of_range(exMsg);
    }
    this->year = yyyy;

    if (validMonth(mm)) {
        this->month = mm;
    }
    else {
        std::string exMsg = "Invalid Month value: " +
                            std::to_string(mm) + ".";
        this->year = currentYear;
        throw std::out_of_range(exMsg);
    }

    if (validDay(dd)) {
        this->day = dd;
    }
    else {
        std::string exMsg = "Invalid Day value: " + std::to_string(dd) +
                            ". Max value allowed: " +
                            std::to_string(daysInMonth(mm)) + ".";
        this->year = currentYear;
        this->month = currentMonth;
        throw std::out_of_range(exMsg);
    }
}

/**
 * Retrieves the current time from the system clock and sets Date values to
 * the current date. Uses local time and default format style.
 * @return Date object encapsulating the current local system clock time.
 */
Date Date::now() {
    struct tm currentTime;
    time_t now = time(nullptr);
    localtime_s(&currentTime, &now);

    int year = currentTime.tm_year + 1900;
    int month = currentTime.tm_mon + 1;
    int day = currentTime.tm_mday;

    return Date(year, month, day);
}

/**
 * Retrieves the current time from the system clock and sets Date values to
 * the current date. Uses local time for determining date and selected format
 * style.
 * @param format DATE_STRING_FORMAT type for formatting Strings of Date
 * @return Date object encapsulating the current local system clock time with
 * selected formatting.
 */
Date Date::now(DATE_STRING_FORMAT format) {
    Date current = now();
    return Date(current.getYear(), current.getMonth(), current.getDay(), format);
}


/**
 * Determines if date 1 comes before date 2.
 * Uses short circuit OR checks to exit early based on descending magnitude.
 * For instance, if year 1 is less than year 2, we know date1 is before date2.
 * But if they are the same year, we then check month, and finally day.
 * If all checks evaluate as false, we know date1 is not before date2.
 * @param date1 The date to check if before.
 * @param date2 The date to check against the before.
 * @return True if date1 is before date2.
 */
bool Date::isBefore(const Date &date1, const Date &date2) noexcept {
    if (date1.year < date2.year) {
        return true;
    }
    if (date1.year == date2.year) {
        if (date1.month < date2.month) {
            return true;
        }
        if (date1.month == date2.month) {
            return date1.day < date2.day;
        }
    }
    return false;
}

/**
 * Determines if this Date object comes before provided date object.
 * @param checkDate The date to check against this.
 * @return True if this Date comes before the checkDate.
 */
bool Date::isBefore(const Date &checkDate) noexcept {
    return Date::isBefore(*this, checkDate);
}

/**
 * Calculates the days between two supplied dates.
 * Order of dates entered does not matter.
 * @param date1 First Date to use for calculation.
 * @param date2 Second Date to use for calculation.
 * @return Integer number of days between the two supplied dates.
 */
int Date::daysBetween(const Date &date1, const Date &date2) noexcept {
    using namespace std;
    using namespace chrono;
    auto start = high_resolution_clock::now();


    if (isBefore(date2, date1)) {
        // flip our inputs and recur
        return daysBetween(date2, date1);
    }

    int days = 0;

    // grab a copy of our first date
    Date temp(date1);

    // increment the copy until it is no longer before the second date and count
    // how many times this happens
    while (isBefore(temp++, date2)) {
        days++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    std::cout << "\n\nExecution time: " << duration.count() * .001
              << " milliseconds\n\n";

    return days;
}

/**
 * Calculates the days between *this Date and the supplied Date value.
 * @param dateToCheck The Date value to check for range.
 * @return An integer of the number of days between *this Date and supplied Date.
 */
int Date::daysBetween(const Date &dateToCheck) noexcept {
    return Date::daysBetween(*this, dateToCheck);
}

/**
 * Returns the days between this Date object and the supplied Date object.
 * If the supplied date is after *this date, will return a negative value.
 * @param subtractDate The date to subtract from *this Date.
 * @return The number of days between *this Date and the supplied date.
 */
int Date::operator-(const Date &subtractDate) noexcept {
    if (!isBefore(subtractDate)) {
        return daysBetween(subtractDate);
    }
    else {
        return -1 * daysBetween(subtractDate);
    }
}

/**
 * Increments the current date held by this by one day and returns a pointer
 * back to this.
 * @return this after incrementing.
 */
Date & Date::nextDay() noexcept {
    if ((this->day) < daysInMonth(this->month)) {
        this->day++;
    }
    else if (this->month < 12) {
        this->month++;
        this->day = 1;
    }
    else {
        this->year++;
        this->month = 1;
        this->day = 1;
    }

    return *this;
}

/**
 * Increment Prefix operator overload.
 * @return *this after being decremented.
 */
Date & Date::operator++() noexcept {
    return this->nextDay();
}

/**
 * Increment postfix operator overload.
 * @return A temp date holding what *this is before incrementing.
 */
Date Date::operator++(int) noexcept {
    Date temp(*this);
    this->nextDay();
    return temp;
}

/**
 * Decrements the current date held by this by one day and returns a pointer
 * back to this.
 * @return this after decrementing.
 */
Date & Date::previousDay() noexcept {
    if (this->day == 1) {
        if (this->month == 1) {
            this->year--;
            this->month = 12;
            this->day = 31;
        }
        else {
            this->month--;
            this->day = daysInMonth(this->month);
        }
    }
    else {
        this->day--;
    }

    return *this;
}

/**
 * Decrement Prefix operator overload.
 * @return *this after being decremented.
 */
Date & Date::operator--() noexcept {
    return this->previousDay();
}

/**
 * Decrement Postfix operator overload.
 * @return A temp date holding what *this is before decrementing.
 */
Date Date::operator--(int) noexcept {
    Date temp(*this);
    this->previousDay();
    return temp;
}

/**
 * Determines if *this Date object is equal to another Date object.
 * Warning: Does not check if both dates use the same format for string formatting!
 * This only validates the date values.
 * @param dateToCheck The date to check against.
 * @return True if *this Date is equal to the dateToCheck.
 */
bool Date::equalDateValues(const Date &dateToCheck) const noexcept {
    return (this->getYear() == dateToCheck.getYear()) &&
           (this->getMonth() == dateToCheck.getMonth()) &&
           (this->getDay() == dateToCheck.getDay());
}

/**
 * Operator overload for checking equality.
 * Unlike equalValues method, this WILL validate that string format selection is the same
 * between objects!
 * @param dateToCheck The date to check against.
 * @return True if *this date is equal to the dateToCheck.
 */
bool Date::operator==(const Date &dateToCheck) const noexcept {
    return this->equalDateValues(dateToCheck) &&
            (this->getDateStringFormat() == dateToCheck.getDateStringFormat());
}

/**
 * Stream insertion operator overload.
 * Sends a full length date string to the stream.
 * @param stream an output stream object to send data to.
 * @param date A date object we wish to stream.
 * @return Full length US formatted string representation of the date.
 */
std::ostream & operator<<(std::ostream &stream, const Date &date) noexcept {
    stream << date.toString();
    return stream;
}

/**
 * Stream extraction operator overload.
 * Takes a string representation of a date and converts it into a Date object.
 * Valid formatting for string input is fairly strict and as such should not
 * be used anywhere user input is required. Individual values should instead be
 * obtained and validated independently using the static methods provided by this
 * class to validate days and months.
 *
 * Valid formats are:
 *      US: MM/DD/YYYY
 *      EU: DD/MM/YYYY
 *
 * The date formatting MUST be set correctly before using this or it could behave
 * in unexpected ways. Note that the default empty constructor for a Date sets
 * the date formatting to the default formatting selection so inputting an EU
 * formatted date string into a freshly initialized Date object without setting
 * the date format will most likely cause an exception or behave contrary to
 * design.
 *
 * This operator is more likely than not going to throw an exception. It should
 * be avoided if possible. Input validation within this operator also violates
 * the single responsibility principle and as such does NOT do it very well.
 *
 * Input should be validated more rigorously outside of using this operator.
 *
 * @param stream A stream object containing a date string
 * @param obj The Date object we wish to set
 * @return A clean stream object
 * @throws std::invalid_argument If formatting of input is incorrect or the values
 * supplied are invalid.
 */
std::istream & operator>>(std::istream &stream, Date &obj) {
    std::string input;
    stream >> input;

    // clear the stream buffer,
    stream.clear();

    // early exception if the length of the string doesn't match expected input
    if (input.length() != 10) {
        throw std::invalid_argument("Invalid input format: " + input);
    }

    // make sure valid delimiter is used and all delimiters are the same
    // 07/31/2019
    bool validDelimiterUsed = input[2] == input[5];
    if (validDelimiterUsed) {
        for (auto delimiter : obj.validDelimiters) {
            validDelimiterUsed = input[2] == delimiter;

            // if still valid, end search
            if (validDelimiterUsed) {
                break;
            }
        }
    }

    // if above check for delimiters failed, bad input
    if (!validDelimiterUsed) {
        throw std::invalid_argument("Invalid input format: " + input);
    }

    // if all of the above is ok, try to set the Date object values using the input
    // if anything fails, catch the possible exceptions and throw a new one with
    // information about what happened.
    try {
        if (obj.getDateStringFormat() == Date::US_LONG || obj.getDateStringFormat() == Date::US_SHORT) {
            int year = std::stoi(input.substr(6,4));
            int month = std::stoi(input.substr(0,2));
            int day = std::stoi(input.substr(3,2));
            obj.setDate(year, month, day);
        }
        else {
            int year = std::stoi(input.substr(6,4));
            int month = std::stoi(input.substr(3,2));
            int day = std::stoi(input.substr(0,2));
            obj.setDate(year, month, day);
        }
    }
    catch (const std::logic_error &ex) { // catch invalid_argument or out_of_range
        throw std::invalid_argument("Invalid Date input: " + input);
    }


    return stream;
}

/**
 * Checks if a year is a leap year (29 days in February).
 * @param year The year to check.
 * @return True if the year is a leap year.
 */
bool Date::isLeapYear(int year) {
    if (year < 0) {
        std::string exMsg = "Invalid Year value: " + std::to_string(year) +
                        ". This class does not currently support BCE years.";
        throw std::out_of_range(exMsg);
    }

    // if divisible by 400, it is a leap year
    if (year % 400 == 0) {
        return true;
    }

    // if divisible by 100 but not 400, not a leap year
    if (year % 100 == 0) {
        return false;
    }

    // if divisible by 4 but not divisible by 100, it is a leap year
    return year % 4 == 0;
}

/**
 * Determines if this->year is a leap year.
 * @return True if this->year is a leap year.
 */
bool Date::isLeapYear() noexcept {
    return isLeapYear(this->year);
}

/**
 * Determines the max number of days given a month and a year.
 * For example, given April, June, September, or November, return 30.
 * For February, will check if it is a leap year or not to determine value.
 * All other months have 31 days.
 * @param year The year of the month to check. Required for leap year checks.
 * @param month The month number value to get the max number of days for.
 * @return The maximum number of days in a given month.
 */
int Date::daysInMonth(int year, int month) {
    static constexpr int monthsWith30Days[] {4, 6, 9, 11};

    if (!validMonth(month)) {
        throw std::out_of_range("Invalid Month");
    }

    if (month == 2) {
        if (isLeapYear(year)) {
            return 29;
        }
        return 28;
    }

    for (int val : monthsWith30Days) {
        if (month == val) {
            return 30;
        }
    }

    return 31;
}

/**
 * Determines the max number of days given a month and this->year.
 * For example, given April, June, September, or November, return 30.
 * For February, will check if it is a leap year or not to determine value.
 * All other months have 31 days.
 * @param month The month number value to get the max number of days for.
 * @return The maximum number of days in a given month.
 */
int Date::daysInMonth(int monthNum) {
    return Date::daysInMonth(this->year, monthNum);
}

/**Getter for this->year*/
int Date::getYear() const noexcept {
    return year;
}

/**Getter for this->month*/
int Date::getMonth() const noexcept {
    return month;
}

/**
 * Returns a string representation for a given month number.
 * @param month int value to find the name of a month for.
 * @return A string representation of the month number
 * @throws std::out_of_range exception if month is not valid
 */
std::string Date::getMonthName(int month) {
    if (!validMonth(month)) {
        std::string exMsg = "Invalid Month value: " +
                            std::to_string(month) + ".";
        throw std::out_of_range(exMsg);
    }

    static std::map<int, std::string> monthNames = {
            {1, "January"},
            {2, "February"},
            {3, "March"},
            {4, "April"},
            {5, "May"},
            {6, "June"},
            {7, "July"},
            {8, "August"},
            {9, "September"},
            {10, "October"},
            {11, "November"},
            {12, "December"}
    };

    return monthNames.at(month);
}

/**
 * Determines the string representation for this->month.
 * Unlike the static class method that determines a month name with a parameter,
 * this will never throw an exception because this->month must be a valid month
 * number in order for *this to exist.
 * @return A string representation of this->month.
 */
std::string Date::getMonthName() const noexcept {
    return Date::getMonthName(this->getMonth());
}

/**Getter for this->day*/
int Date::getDay() const noexcept {
    return day;
}

/**
 * Setter for this->dateStringFormat.
 * @throws std::invalid_argument if attempt to set to Date::LAST.
 * */
void Date::setDateStringFormat(Date::DATE_STRING_FORMAT newFormat) {
    if (newFormat == LAST) {
        throw std::invalid_argument("Last value is only for iteration. Do not set values to this.");
    }
    this->dateStringFormat = newFormat;
}
/**Getter for this->dateStringFormat*/
Date::DATE_STRING_FORMAT Date::getDateStringFormat() const noexcept {
    return this->dateStringFormat;
}

/**
 * Get a string for displaying what the current date format is.
 * @return A string representation of this->dateStringFormat.
 */
std::string Date::getDateStringFormatDisplayString() const noexcept {
    switch (this->getDateStringFormat()) {
        case US_SHORT: return "US Short";
        case US_LONG: return "US Long";
        case EU_SHORT: return "EU Short";
        case EU_LONG: return "EU Long";
        case LAST: return "";
    }
}

/**Getter for this->validDelimiters*/
const std::set<char> &Date::getValidDelimiters() const noexcept {
    return validDelimiters;
}

/**Setter for this->validDelimiters*/
void Date::setValidDelimiters(const std::set<char> &delimiters) noexcept {
    this->validDelimiters = delimiters;
}

/**
 * Adds a character to the set of delimiters.
 * Returns true if delimiter was not already in the set and was added.
 * Returns false if the delimiter was already in the set.
 * @param delimiter The character we want to add to the set.
 * @return True if successfully inserted.
 */
bool Date::addDelimiter(char delimiter) noexcept {
    auto it = validDelimiters.insert(delimiter);

    return it.second;
}

/**
 * Removes a character from the list of valid delimiters.
 * Does not allow removal of delimiters if there is only one in the set.
 * If the character is not in the list or cannot be erased, this method will
 * return False.
 * @param delimiter The delimiter we want to remove.
 * @return True if the character was removed successfully.
 */
bool Date::removeDelimiter(char delimiter) noexcept {
    size_t success = 0;
    if (validDelimiters.size() > 1) {
        success = validDelimiters.erase(delimiter);
    }

    return success > 0;
}

/**
 * Creates a string representation of *this Date based a format set either
 * during construction or using setDateStringFormat(format).
 * @return A string representation of *this Date.
 */
std::string Date::toString() const noexcept {
    return toString(this->getDateStringFormat());
}

/**
 * Creates a string representation of *this Date based on the supplied format.
 * @param format The format we wish to use to format a date.
 * @return A string representation of *this Date.
 */
std::string Date::toString(Date::DATE_STRING_FORMAT format) const noexcept {
    using std::string;
    using std::to_string;

    string year = to_string(this->getYear());

    // if before 1000, prepend 0's to the string representation of year
    while (year.length() < 4) {
        year.insert(0, "0");
    }

    string month = to_string(this->getMonth());
    string monthName = this->getMonthName();
    string day = to_string(this->getDay());

    if (format == US_SHORT) {
        return month + "/" + day + "/" + year;
    }

    if (format == US_LONG) {
        return monthName + " " + day + ", " + year;
    }

    if (format == EU_SHORT) {
        return day + "/" + month + "/" + year;
    }

    if (format == EU_LONG) {
        return day + " " + monthName + " " + year;
    }

    return "";
}

////////////////////////////////////////////////////////////////////////////////
/// PRIVATE METHODS
////////////////////////////////////////////////////////////////////////////////

/**
 * Checks if a numerical value for a month is valid or not.
 * @param num The numerical value to check.
 * @return True if the value entered is a valid month number.
 */
bool Date::validMonth(int num) noexcept {
    return num > 0 && num <= 12;
}

/**
 * Checks if a numerical value for a day is valid or not based on this->year and
 * this->month.
 * @param num The numerical value to check.
 * @return True if value entered is a valid day for this->year and this->month.
 */
bool Date::validDay(int num) noexcept {
    return num >= 1 && num <= daysInMonth(this->month);
}



