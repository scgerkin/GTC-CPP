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

// regex for coordinates for checkers game
// allows A1 or 1A but nothing outside A-H, 1-8
bool regex_checkers_coord(string test) {
    regex p("^([a-hA-H][1-8])|([1-8][a-hA-H])$");

    return regex_match(test, p);
}

// email
/*
http://regexlib.com/UserPatterns.aspx?authorId=15777db1-4c90-48f2-b323-905b509f16e8
Email validator that adheres directly to the specification for email address
naming. It allows for everything from ipaddress and country-code domains, to
very rare characters in the username.
Credit: Andy Smith
*/
bool regex_email(string test) {
    regex p("^([a-zA-Z0-9_\\-\\.]+)@((\\[[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.)|(([a-zA-Z0-9\\-]+\\.)+))([a-zA-Z]{2,4}|[0-9]{1,3})(\\]?)$");

    return regex_match(test, p);
}

// regex for usernames
// 4-32 alphanumeric characters only
// allows '.' or '_' but not at beginning, end, or repeated
bool regex_username(string test) {
    regex p("^[a-zA-Z0-9]([._](?![._])|[a-zA-Z0-9]){2,30}[a-zA-Z0-9]$");
    
    return regex_match(test, p);
}

// regex for creating a password
// this sets to medium strength:
// min 4 characters
// contains at least 1 number
// max 32 characters
bool regex_password(string test) {
    regex p("^(?=.*\\d).{4,32}$");

    return (regex_match(test, p));
}

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

// hex validator with or with out leading "0x", case insensitive
bool regex_hex(string test) {
    regex p("^[0]?[x]?[0-9a-f]+$", regex_constants::icase);
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