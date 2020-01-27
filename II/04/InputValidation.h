#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <regex>

/**Validates Yes or No option selection.
Uses regular expression parsing to match input against valid “Y” or “N” entry
only. Case insensitive.

@param input – String value to validate.
@return True if input matches “Y” or “N”
*/
bool validYN(const std::string &input) {
    // verifies that string input is only "Y" or "N", case insensitive
    std::regex pattern("([Y|N])", std::regex_constants::icase);
    return std::regex_match(input, pattern);
}

/**Validates Unsigned Integer numbers.
Uses regular expression parsing to match input against valid unsigned integer
values.

@param input - String value to validate.
@return True if input consists only of an unsigned integer value.
*/
bool validUnsignedInt(const std::string &input) {
    // verifies that string input is an unsigned integer
    std::regex pattern("(^[0-9]+[0-9]*$)");
    return std::regex_match(input, pattern);
}

/**Validates Unsigned Floating-point numbers.
Uses regular expression parsing to match input against valid unsigned
floating-point number values.

@param input - String value to validate.
@return True if the input consists only of an unsigned floating-point number
    value.
*/
bool validUnsignedFloat(const std::string &input) {
    std::regex pattern("([0-9]+)(\\.(([0-9]+)?))?");
    return std::regex_match(input, pattern);
}

#endif // !INPUT_VALIDATION_H

