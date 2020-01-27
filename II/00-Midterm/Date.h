#ifndef DATE_H
#define DATE_H

#include <stdexcept>
#include <vector>
#include <set>

/**
 * Date class encapsulates and represents a date in the Gregorian calendar.
 *
 * Inputs are assumed to be valid dates within Gregorian calendar (meaning any
 * date entered before October 1582 should be considered only an estimate when
 * calculating number of days between dates when before this point in time).
 *
 * Any year entry prior to 0 CE (1 BCE or prior) is not supported by this class.
 * Hypothetically, this class should be able to support any year up to 2147483647,
 * but this is definitely not recommended and has not been tested. Additionally,
 * attempting to calculate the date range between the beginning of the Common Era
 * and the year 2147483647 will take a considerable amount of processor time as
 * the time complexity of computing this is O(n).
 *
 * Except when using the istream extraction operator ( >> ), all Date values
 * should be entered in descending order of magnitude (YYYY/MM/DD) to follow
 * standard programming protocols for DateTime recording.
 *
 * The exclusion for the >> operator is to allow user or file input given a
 * specific formatting style. For instance, if the user is accustomed to entering
 * dates in the form MM/DD/YYYY, this can be accomplished by setting the format
 * using the DATE_STRING_FORMAT enumerator to US_SHORT or US_LONG.
 *
 * The class provides several methods for modifying the values of a date and
 * methods for calculating the differences between dates. Further information
 * about these methods can be found internally documented with each function
 * definition or with each class method description in the external documentation.
 *
 * Exception Safety:
 *      Methods that are exception safe are explicitly marked noexcept.
 *      All constructors (except copy constructor) and methods to change the
 *      date values can throw std::out_of_range exceptions for invalid dates
 *      values.
 *      For more detail, see each individual method description.
 * Thread Safety:
 *      To modify or change the existing values of a Date object, one must change
 *      all three values at method call or instantiation. However, the current
 *      string format option and the list of valid delimiters can be changed
 *      independently of changing the values of a date. Therefore, it is wise
 *      to consider this class NOT thread safe overall but can be considered
 *      probably safe if no modifications are to be done after initialization of
 *      formatting choice and delimiters.
 *
 *      Thread safety has not been tested and this class is not designed to
 *      fulfill that purpose.
 */
class Date {
public:
    enum DATE_STRING_FORMAT { // For determining string format of dates.
        US_SHORT,   // Example: 07/18/2019
        US_LONG,    // Example: July 18, 2019
        EU_SHORT,   // Example: 18/07/2019
        EU_LONG,    // Example: 18 July 2019
        LAST        // DO NOT USE, FOR ITERATING PURPOSES ONLY
    };
private: // member vars
    int year;
    int month;
    int day;
    DATE_STRING_FORMAT dateStringFormat;
    std::set<char> validDelimiters;
public: // methods
    Date() noexcept;
    Date(int year, int month, int day, DATE_STRING_FORMAT format);
    Date(int year, int month, int day);
    Date(const Date &obj) noexcept;
    void setDate(int yyyy, int mm, int dd);
    static Date now();
    static Date now(DATE_STRING_FORMAT format);
    static bool isBefore(const Date &date1, const Date &date2) noexcept;
    bool isBefore(const Date &checkDate) noexcept;
    static int daysBetween(const Date &date1, const Date &date2) noexcept;
    int daysBetween(const Date &dateToCheck) noexcept;
    int operator-(const Date &subtractDate) noexcept;
    Date & nextDay() noexcept;
    Date & operator++() noexcept;//prefix
    Date operator++(int) noexcept;//postfix
    Date & previousDay() noexcept;
    Date & operator--() noexcept;//prefix
    Date operator--(int) noexcept;//postfix
    bool equalDateValues(const Date &dateToCheck) const noexcept;
    bool operator==(const Date &dateToCheck) const noexcept;
    friend std::ostream & operator<<(std::ostream &stream, const Date &date) noexcept;
    friend std::istream & operator>>(std::istream &stream, Date &obj);
    static bool isLeapYear(int year);
    bool isLeapYear() noexcept;
    static int daysInMonth(int year, int month);
    int daysInMonth(int monthNum);
    int getYear() const noexcept;
    int getMonth() const noexcept;
    static std::string getMonthName(int month);
    std::string getMonthName() const noexcept;
    int getDay() const noexcept;
    void setDateStringFormat(DATE_STRING_FORMAT newFormat);
    DATE_STRING_FORMAT getDateStringFormat() const noexcept;
    std::string getDateStringFormatDisplayString() const noexcept;
    const std::set<char> & getValidDelimiters() const noexcept;
    void setValidDelimiters(const std::set<char> &delimiters) noexcept;
    bool addDelimiter(char delimiter) noexcept;
    bool removeDelimiter(char delimiter) noexcept;
    std::string toString() const noexcept;
    std::string toString(DATE_STRING_FORMAT format) const noexcept;

    ~Date() = default;

private: // methods
    static bool validMonth(int num) noexcept;
    bool validDay(int num) noexcept;
};


#endif DATE_H
