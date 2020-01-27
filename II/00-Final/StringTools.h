/**
 * Contains functions for manipulating std::string types.
 */
#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include <string>
#include <vector>

using std::string;

/**Used by functions to identify any whitespace characters*/
const string WHITESPACE_CHARS = " \n\r\t\f\v";

string trim(const string &str);
string ltrim(const string &str);
string rtrim(const string &str);
string toLower(const string &str);
string toUpper(const string &str);
std::vector<string> breakUpStringByWhitespace(const string &str);
string removePunctuation(const string &str);
std::vector<string> getListOfWords(const string &sentence);
string capitalizeWord(const string &word);
string setPascalCase(const string &sentence);



#endif //STRINGTOOLS_H
