#ifndef INPUT_VALIDATION_H
#define INPUT_VALIDATION_H
#include <regex>

bool validYN(const std::string &input) {
    // verifies that string input is only "Y" or "N", case insensitive
    std::regex pattern("([Y|N])", std::regex_constants::icase);
    return std::regex_match(input, pattern);
}

bool validUnsignedInt(const std::string &input) {
    // verifies that string input is an unsigned integer
    std::regex pattern("(^[0-9]+[0-9]*$)");
    return std::regex_match(input, pattern);
}

bool validUnsignedFloat(const std::string &input) {
    // verifies that string input is an unsigned floating point number
    std::regex pattern("([0-9]+)(\\.(([0-9]+)?))?");
    return std::regex_match(input, pattern);
}

#endif // !INPUT_VALIDATION_H

