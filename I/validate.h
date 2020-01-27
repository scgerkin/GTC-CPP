/*
    Header for regex validation function
    that allows one function to work for multiple values to check against
    Uses global variables to allow multiple other functions to call
    the validations
    Global variables MUST be string and a valid regex function

    USE THE FOLLOWING FOR INPUT
    getline(cin, inputValue);

    Otherwise blank spaces will be allowed and cause a glitch with input

   ************************NOTE FOR CURRENCY VALIDATION************************
  * Currency validation allows for a numeral seperator entry (",") for every   *
  * 3rd digit before decimal space.                                            *
  * If using this currency validation, you will have to remove the commas for  *
  * conversion into a double datatype or entry with commas will return a       *
  * different value.                                                           *
  * EG                                                                         *
  * Input -> 1,000.00                                                          *
  * Output -> 1                                                                *
  * This function ONLY returns boolean value for input matching the patterns   *
  * Functionality to validate a currency entry and return a double without     *
  * Seperators may be added later.                                             *
   ****************************************************************************

*/
#pragma once
#include <regex>
#include <string>
using namespace std;

// "Y" "y" "N" "n"
bool regex_yn(string test) {
    regex p("Y|N", regex_constants::icase);
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// custom case 1 character
bool regex_char(string test, char ch1) {
    //pattern builder
    string pb = "";
    pb.push_back(ch1);

    regex p(pb, regex_constants::icase);

    if (regex_match(test, p))
        return true;
    else
        return false;
}

// custom case 2 characters
bool regex_2char(string test, char ch1, char ch2) {
    //pattern builder
    string pb = "";
    pb.push_back(ch1);
    pb += "|";
    pb.push_back(ch2);

    regex p(pb, regex_constants::icase);

    if (regex_match(test, p))
        return true;
    else
        return false;
}

// unsigned int
bool regex_u_int(string test) {
    regex p("(^[0-9]+[0-9]*$)");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// signed or unsigned int
bool regex_int(string test) {
    regex p("(^[+-]?[0-9]+[0-9]*$)");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// unsigned floating point number
bool regex_u_float(string test) {
    regex p("([[:digit:]]+)(\\.(([[:digit:]]+)?))?");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// signed or unsigned floating point number
bool regex_float(string test) {
    regex p("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// scientific notation, or "e" notation
bool regex_e_notation(string test) {
    regex p("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// unsigned currency value with comma thousands seperator
bool regex_u_currency(string test) {
    regex p("^[0-9]{1,3}(?:,?[0-9]{3})*(?:.[0-9]{2})?$");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// signed or unsigned currency value with comma thousands seperator
bool regex_currency(string test) {
    regex p("^[+-]?[0-9]{1,3}(?:,?[0-9]{3})*(?:.[0-9]{2})?$");
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// custom case insensitive
bool regex_custom_icase(string test, string pattern) {
    regex p(pattern, regex_constants::icase);
    if (regex_match(test, p))
        return true;
    else
        return false;
}

// custom case sensitive
bool regex_custom_case(string test, string pattern) {
    regex p(pattern);
    if (regex_match(test, p))
        return true;
    else
        return false;
}