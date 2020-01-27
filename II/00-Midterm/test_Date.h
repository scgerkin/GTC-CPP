#ifndef TEST_DATE_H
#define TEST_DATE_H

#include "Date.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

class test_Date {
public:
    test_Date() {
        bool allTestsPassed = runAll();
        std::cout << "\n\n";
        if (allTestsPassed) {
            std::cout << "***ALL TESTS PASSING***";
        }
        else {
            std::cout << "****************TEST FAILURES****************";
        }
        std::cout << "\n\n";
    }
    static bool runAll();
    static bool test_ConstructorThrowsExceptionsForBadInput();
    static bool test_ConstructorDoesNotThrowExceptionsForUnusualValidInput();
    static bool test_static_daysBetween();
    static bool test_member_daysBetween();
    static bool test_subtractOperator();
    static bool test_equalDateValues();
    static bool test_equalityOperator();
    static bool test_nextDay();
    static bool test_static_isBefore();
    static bool test_member_isBefore();
    static bool test_incrementPrefixOperator();
    static bool test_incrementPostfixOperator();
    static bool test_previousDay();
    static bool test_decrementPostfixOperator();
    static bool test_decrementPrefixOperator();
    static bool test_istreamOperatorOverloadWithGoodInput();
    static bool test_istreamOperatorOverloadWithBadFormatInputThrowsException();
    static bool test_istreamOperatorOverloadWithInvalidFormatThrowsException();
    static bool test_static_isLeapYear();
    static bool test_member_isLeapYear();
    static bool test_static_daysInMonth();
    static bool test_member_daysInMonth();
    static bool test_static_getMonthName();
    static bool test_member_getMonthName();
};


#endif //INC_00_MIDTERM_TEST_DATE_H
