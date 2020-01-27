#include "Month.h"

// instantiate the static map object used by the class
std::map<std::string, int> Month::mapOfMonthNameNumber;

/** Default no-arg constructor.
Sets number to 1 and name to "January".
*/
Month::Month() : name("JANUARY"), number(1) {
    if (mapOfMonthNameNumber.empty()) {
        fillMap();
    }
}

/** Constructor with name as starting value.
@param monthName the name of the month to initialize with.
*/
Month::Month(const std::string &monthName) : name(monthName) {
    if (mapOfMonthNameNumber.empty()) {
        fillMap();
    }
    determineNumber();
}

/** Constructor with number as starting value.
@param monthNumber the number of the month to initialize with.
*/
Month::Month(const int &monthNumber) : number(monthNumber) {
    if (mapOfMonthNameNumber.empty()) {
        fillMap();
    }
    determineName();
}

/** Deep-copy constructor.
@param obj the Month object to copy.
*/
Month::Month(const Month &obj) {
    if (mapOfMonthNameNumber.empty()) { // it'd be pretty wild if this happened
        fillMap();
    }
    this->name = obj.name;
    this->number = obj.number;
}

/** Setter for name.
WARNING: Input is not validated.
@param monthName name of month to set to
*/
void Month::setName(const std::string &monthName) {

    this->name = monthName;
    determineNumber();
}

/** Setter for number.
WARNING: Input is not validated.
@param monthNumber number of month to set to
*/
void Month::setNumber(const int &monthNumber) {
    this->number = monthNumber;
    determineName();
}

/** Getter for name.
@return this->name
*/
std::string Month::getName() {
    return this->name;
}

/** Getter for number.
@return this->number
*/
int Month::getNumber() {
    return this->number;
}

/** Operator overload for increment operator (prefix).
Increments this->number and then determines the name.
If month is incremented past 12, it is reset to 1.
*/
Month Month::operator++() {
    number = (number < 12) ? (number + 1) : 1;
    this->determineName();
    return *this;
}

/** Operator overload for increment operator (postfix).
Works as above but with holds and returns the current Month object.
*/
Month Month::operator++(int) {
    Month temp(number);
    number = (number < 12) ? (number + 1) : 1;
    determineName();
    return temp;
}

/** Operator overload for decrement operator (prefix).
Decrements this->number and then determines the name.
If month is decremented to 0, it is reset to 12.
*/
Month Month::operator--() {
    number = (--number == 0) ? 12 : number;
    this->determineName();
    return *this;
}

/** Operator overload for decrement operator (postfix).
Works as above but with holds and returns the current Month object.
*/
Month Month::operator--(int) {
    Month temp(number);
    number = (--number == 0) ? 12 : number;
    determineName();
    return temp;
}

/** Operator overload for cout insertion operator.
Sends a string representation of the Month object to the output stream.
@param stream The outputstream to send to.
@param obj The month object being sent to the stream.
@return The constructed stream.
*/
std::ostream & operator<<(std::ostream &stream, const Month &obj) {
    stream << "Month name: " << obj.name << " number: " << obj.number;
    return stream;
}

/** Operator overload for cin extraction operator.
Takes integer or string value from stream and sets appropriate value to stream
value, then determines number or name of month as needed.
WARNING: Input is not validated!
@param stream The input stream being used to capture input.
@param obj The month object to capture input into.
@return The stream object used for input.
*/
std::istream & operator>>(std::istream &stream, Month &obj) {
    //FIXME: input validation

    std::string input;
    std::locale loc;
    
    stream >> input;

    if (isdigit(input[0])) {
        obj.setNumber(std::stoi(input));
    }
    else {
        std::string name = "";
        for (char c : input) {
            name += toupper(c);
        }
        obj.setName(name);
    }
    return stream;
}

/** Destructor.
Requires no implementation.
*/
Month::~Month() {}

/** Private method to fill the mapOfMonthNameNumber object with months and
    corresponding number values.
Should only be called the first time a Month object is instantiated but the
method checks to make sure the map is empty before adding values for
added safety.
*/
void Month::fillMap() {
    if (mapOfMonthNameNumber.empty()) {
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("JANUARY", 1));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("FEBRUARY", 2));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("MARCH", 3));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("APRIL", 4));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("MAY", 5));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("JUNE", 6));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("JULY", 7));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("AUGUST", 8));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("SEPTEMBER", 9));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("OCTOBER", 10));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("NOVEMBER", 11));
        mapOfMonthNameNumber.insert(std::pair<std::string, int>("DECEMBER", 12));
    }
}

/** Private method to determine the name of the month corresponding to the set
    number value.
Iterates over the hash map containing month names comparing the number to
each element value in the map.
If a value is found, name is set to the map key.
If no match is found, the name is set to UNKNOWN.
*/
void Month::determineName() {
    name = "UNKNOWN";

    for (auto element : mapOfMonthNameNumber) {
        if (number == element.second) {
            name = element.first;
            break;
        }
    }
}

/** Private method to determine the number of the month corresponding to the set
    name value.
Uses a hash map to find the corresponding number by the name.
If no element is found with the name, the number is set to -1.
*/
void Month::determineNumber() {
    auto element = mapOfMonthNameNumber.find(name);
    if (element != mapOfMonthNameNumber.end()) {
        number = element->second;
    }
    else {
        number = -1;
    }
}
