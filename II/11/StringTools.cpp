#include <algorithm>
#include <sstream>
#include <deque>
#include "StringTools.h"

/**
 * Trims whitespace off the beginning and end of a string.
 * @param str The string to trim.
 * @return A string with no extra whitespace on left or right side.
 */
string trim(const string &str) {
    return rtrim(ltrim(str));
}

/**
 * Trims the left (beginning) side of a string of whitespace.
 * @param str The string to trim.
 * @return A string with no leading whitespace.
 */
string ltrim(const string &str) {
    auto start = str.find_first_not_of(WHITESPACE_CHARS);
    return (start == std::string::npos) ? "" : str.substr(start);
}

/**
 * Trims the right (end) side of a string of whitespace.
 * @param str The string to trim.
 * @return A string with no following whitespace.
 */
string rtrim(const string &str) {
    auto end = str.find_last_not_of(WHITESPACE_CHARS);
    return (end == std::string::npos) ? "" : str.substr(0, end + 1);
}

/**
 * Converts every character of a string to lower case.
 * @param str The string to manipulate.
 * @return The same string with all lower case characters.
 */
string toLower(const string &str) {
    string result = str;

    std::for_each(result.begin(), result.end(), [](char &c) {
        c = ::tolower(c);
    });

    return result;
}

/**
 * Converts every character of a string to Upper Case.
 * @param str The string to manipulate.
 * @return The same string with all Upper Case characters.
 */
string toUpper(const string &str) {
    string result = str;

    std::for_each(result.begin(), result.end(), [](char &c) {
        c = ::toupper(c);
    });

    return result;
}

/**
 * Breaks up a string into its composite words using whitespace as a delimiter.
 * @param str The string from which we want to extract individual words.
 * @return A vector containing each individual word.
 */
std::vector<string> breakUpStringByWhitespace(const string &str) {
    std::istringstream buffer(trim(str));
    std::vector<string> result;

    while (buffer) {
        string piece;
        buffer >> piece;
        result.push_back(piece);
    }

    return result;
}

/**
 * Removes punctuation from a string using std::ispunct.
 * @param str The string to manipulate.
 * @return A string with no punctuation.
 */
string removePunctuation(const string &str) {
    string result;
    std::remove_copy_if(
            str.begin(), str.end(), std::back_inserter(result),
            std::ptr_fun<int, int>(&std::ispunct)
    );
    return result;
}

/**
 * Gets a list of words broken up by whitespace and punctuation.
 * @param sentence The sentence we wish to extract words from.
 * @return A list of words in a sentence.
 */
std::vector<string> getListOfWords(const string &sentence) {
    std::vector<string> buffer = breakUpStringByWhitespace(sentence);
    std::vector<string> result;

    for (string s : buffer) {
        result.push_back(removePunctuation(s));
    }

    return result;
}

/**
 * Capitalizes a single word by capitalizing the first letter of a given string.
 * @param word The word we wish to capitalize.
 * @return The same string with the first character not whitespace capitalized.
 */
string capitalizeWord(const string &word) {
    string result = word;
    auto start = result.find_first_not_of(WHITESPACE_CHARS);
    result[start] = toupper(result[start]);
    return result;
}

/**
 * Creates a sentence in Pascal Case from a given string.
 * This function maintains any whitespace or punctuation inside the sentence.
 * It does this by iterating over the sentence string, adding each character to
 * a double-ended queue. At each character of the sentence, if the previous
 * character was a letter, the character is added to the queue.
 * If the previous character was not a letter and the current character
 * is a letter, that letter is capitalized and added to the queue. The queue
 * is then converted to a string and returned.
 * Because this is only checking for alpha characters, there are edge cases that
 * should be considered when using this function. An example is the string:
 * "hi 1hello" will return "Hi 1Hello" which may not be desirable.
  * @param sentence The sentence we want in Pascal Case.
 * @return A string of Pascal Case Words maintaining all other formatting from
 *         the parameter sentence.
 */
string setPascalCase(const string &sentence) {
    std::deque<char> deque;

    for (char c : sentence) {
        if (deque.empty() || !isalpha(c) || isalpha(deque.back())) {
            deque.push_back(c);
        }
        else {
            deque.push_back(toupper(c));
        }
    }

    std::string result(deque.begin(), deque.end());
    return result;
}