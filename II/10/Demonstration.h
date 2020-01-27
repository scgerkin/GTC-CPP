#ifndef BALANCEPARENTHESES_DEMONSTRATION_H
#define BALANCEPARENTHESES_DEMONSTRATION_H

#include <string>
#include "StringChecker.h"

/**
 * Basic class for demonstrating the StringChecker utility class.
 */
class Demonstration {
private:
    static const std::string QUIT_STR;
public:
    Demonstration();
private:
    void displayIntroMsg();
    std::string getUserInput();
    void displayIsBalanced(const std::string &str);
};


#endif //BALANCEPARENTHESES_DEMONSTRATION_H
