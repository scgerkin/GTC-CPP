#include "test_Date.h"

bool test_Date::runAll() {
    return
            test_ConstructorThrowsExceptionsForBadInput() &&
                    test_ConstructorDoesNotThrowExceptionsForUnusualValidInput() &&
            test_static_isBefore() &&
            test_member_isBefore() &&
            test_static_daysBetween() &&
            test_member_daysBetween() &&
                    test_subtractOperator() &&
                    test_equalDateValues() &&
                    test_equalityOperator() &&
                    test_nextDay() &&
                    test_incrementPrefixOperator() &&
                    test_incrementPostfixOperator() &&
                    test_previousDay() &&
                    test_decrementPostfixOperator() &&
                    test_decrementPrefixOperator() &&
                    test_istreamOperatorOverloadWithGoodInput() &&
                    test_istreamOperatorOverloadWithBadFormatInputThrowsException() &&
                    test_istreamOperatorOverloadWithInvalidFormatThrowsException() &&
                    test_static_isLeapYear() &&
                    test_member_isLeapYear() &&
                    test_static_daysInMonth() &&
                    test_member_daysInMonth() &&
                    test_static_getMonthName() &&
                    test_member_getMonthName();
}

/**
 * Verifies that the the constructor throws an exception for bad date values.
 * Examples of a bad date are any day greater than 32, days greater than 30 for
 * months only containing 30 days, etc.
 * Anything BCE is checked.
 * @return True if all test cases pass.
 */
bool test_Date::test_ConstructorThrowsExceptionsForBadInput() {
    std::vector<std::tuple<int, int, int>> testCases;
    testCases.emplace_back(2019, 1, 0);
    testCases.emplace_back(2019, 0, 1);
    testCases.emplace_back(-1, 1, 1);
    testCases.emplace_back(2019, 13, 1);
    testCases.emplace_back(2019, 1, 32);
    testCases.emplace_back(2019, 2, 29);
    testCases.emplace_back(2016, 2, 30);
    testCases.emplace_back(2019, 3, 32);
    testCases.emplace_back(2019, 4, 31);
    testCases.emplace_back(2019, 5, 32);
    testCases.emplace_back(2019, 6, 31);
    testCases.emplace_back(2019, 7, 32);
    testCases.emplace_back(2019, 8, 32);
    testCases.emplace_back(2019, 9, 31);
    testCases.emplace_back(2019, 10, 32);
    testCases.emplace_back(2019, 11, 31);
    testCases.emplace_back(2019, 12, 32);

    std::cout << "TEST: Constructor throws exceptions for bad input ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        try {
            int year = std::get<0>(test);
            int month = std::get<1>(test);
            int day = std::get<2>(test);
            Date(year, month, day, Date::US_SHORT);

            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Year value: " << year << " Month value: " << month << " Day value: " << day << "\n";

            allPassing = false;
        }
        catch (const std::out_of_range &ex) {
            // this is good, continue
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies that the constructor does not throw exceptions for valid input that
 * is uncommon.
 * This tests a few leap years and for allowing 29 days.
 * Also checks for January 1st, 0 CE just to verify that the year check allows
 * 0 input.
 * @return True if all test cases pass.
 */
bool test_Date::test_ConstructorDoesNotThrowExceptionsForUnusualValidInput() {
    std::vector<std::tuple<int, int, int>> testCases;
    testCases.emplace_back(0, 1, 1);
    testCases.emplace_back(2016, 2, 29);
    testCases.emplace_back(2012, 2, 29);
    testCases.emplace_back(2008, 2, 29);
    //todo add more tests cases

    std::cout << "TEST: Constructor does not throw exceptions for unusual valid input ... ";

    bool allPassing = true;
    int year = 0;
    int month = 0;
    int day = 0;
    for (auto test : testCases) {
        try {
            year = std::get<0>(test);
            month = std::get<1>(test);
            day = std::get<2>(test);
            Date(year, month, day, Date::US_SHORT);
        }
        catch (const std::out_of_range &ex) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Year value: " << year << " Month value: " << month << " Day value: " << day << "\n";

            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies that the static method isBefore() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_static_isBefore() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 1), false);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 2), true);
    testCases.emplace_back(Date(2012, 1, 2), Date(2012, 1, 1), false);
    testCases.emplace_back(Date(2011, 12, 31), Date(2012, 1, 1), true);
    testCases.emplace_back(Date(2012, 1, 1), Date(2011, 12, 31), false);
    testCases.emplace_back(Date(2011, 06, 5), Date(2011, 7, 5), true);
    testCases.emplace_back(Date(2011, 07, 5), Date(2011, 6, 5), false);
    testCases.emplace_back(Date(2011, 1, 1), Date(2012, 1, 1), true);
    testCases.emplace_back(Date(2012, 1, 1), Date(2011, 1, 1), false);

    std::cout << "TEST: static isBefore() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        bool returnVal = Date::isBefore(std::get<0>(test), std::get<1>(test));
        bool actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal) ? "TRUE" : "FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies that the member method isBefore() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_member_isBefore() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 1), false);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 2), true);
    testCases.emplace_back(Date(2012, 1, 2), Date(2012, 1, 1), false);
    testCases.emplace_back(Date(2011, 12, 31), Date(2012, 1, 1), true);
    testCases.emplace_back(Date(2012, 1, 1), Date(2011, 12, 31), false);
    testCases.emplace_back(Date(2011, 06, 5), Date(2011, 7, 5), true);
    testCases.emplace_back(Date(2011, 07, 5), Date(2011, 6, 5), false);
    testCases.emplace_back(Date(2011, 1, 1), Date(2012, 1, 1), true);
    testCases.emplace_back(Date(2012, 1, 1), Date(2011, 1, 1), false);

    std::cout << "TEST: member isBefore() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        bool returnVal = std::get<0>(test).isBefore(std::get<1>(test));
        bool actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal) ? "TRUE" : "FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies that the static method daysBetween() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_static_daysBetween() {
    std::vector<std::tuple<Date, Date, int>> testCases;
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 1), 0);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 2, 28), 58);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 3, 1), 60);
    testCases.emplace_back(Date(2011, 6, 30), Date(2012, 6, 30), 366);
    testCases.emplace_back(Date(2011, 1, 1),  Date(2012, 8, 8), 585);
    testCases.emplace_back(Date(1580, 1, 1),  Date(2013, 12, 31), 158515);
    testCases.emplace_back(Date(1800, 1, 1),  Date(2019, 5, 17), 80124);
    testCases.emplace_back(Date(1850, 1, 1),  Date(2019, 5, 17), 61862);
    testCases.emplace_back(Date(1900, 1, 1),  Date(1999, 12, 31), 36523);
    testCases.emplace_back(Date(2019, 5, 17), Date(2019, 5, 15), 2);

    std::cout << "TEST: static daysBetween() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = Date::daysBetween(std::get<0>(test), std::get<1>(test));
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies that the member method daysBetween() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_member_daysBetween() {
    std::vector<std::tuple<Date, Date, int>> testCases;
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 1), 0);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 2, 28), 58);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 3, 1), 60);
    testCases.emplace_back(Date(2011, 6, 30), Date(2012, 6, 30), 366);
    testCases.emplace_back(Date(2011, 1, 1),  Date(2012, 8, 8), 585);
    testCases.emplace_back(Date(1580, 1, 1),  Date(2013, 12, 31), 158515);
    testCases.emplace_back(Date(1800, 1, 1),  Date(2019, 5, 17), 80124);
    testCases.emplace_back(Date(1850, 1, 1),  Date(2019, 5, 17), 61862);
    testCases.emplace_back(Date(1900, 1, 1),  Date(1999, 12, 31), 36523);
    testCases.emplace_back(Date(2019, 5, 17), Date(2019, 5, 15), 2);

    std::cout << "TEST: member daysBetween() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = Date::daysBetween(std::get<0>(test), std::get<1>(test));
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies that the subtraction override returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_subtractOperator() {
    std::vector<std::tuple<Date, Date, int>> testCases;
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 1), 0);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 1, 2), -1);
    testCases.emplace_back(Date(2012, 1, 2), Date(2012, 1, 1), 1);
    testCases.emplace_back(Date(2012,2,28), Date(2012,1,1), 58);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 2, 28), -58);
    testCases.emplace_back(Date(2012,3,1), Date(2012,1,1), 60);
    testCases.emplace_back(Date(2012, 1, 1), Date(2012, 3, 1), -60);
    testCases.emplace_back(Date(2012, 6, 30), Date(2011, 6, 30), 366);
    testCases.emplace_back(Date(2011, 6, 30), Date(2012, 6, 30), -366);
    testCases.emplace_back(Date(2012, 8, 8), Date(2011, 1, 1), 585);
    testCases.emplace_back(Date(2011, 1, 1),  Date(2012, 8, 8), -585);
    testCases.emplace_back(Date(2013, 12, 31), Date(1580, 1, 1), 158515);
    testCases.emplace_back(Date(1580, 1, 1),  Date(2013, 12, 31), -158515);
    testCases.emplace_back(Date(2019, 5, 17), Date(1800,1,1), 80124);
    testCases.emplace_back(Date(1800, 1, 1),  Date(2019, 5, 17), -80124);
    testCases.emplace_back(Date(2019,5,17), Date(1850,1,1), 61862);
    testCases.emplace_back(Date(1850, 1, 1),  Date(2019, 5, 17), -61862);
    testCases.emplace_back(Date(1999,12,31), Date(1900,1,1), 36523);
    testCases.emplace_back(Date(1900, 1, 1),  Date(1999, 12, 31), -36523);
    testCases.emplace_back(Date(2019,5,15), Date(2019,5,17), -2);
    testCases.emplace_back(Date(2019, 5, 17), Date(2019, 5, 15), 2);

    std::cout << "TEST: operator overload (-) ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = std::get<0>(test) - std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the method equalDateValues() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_equalDateValues() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), true);
    testCases.emplace_back(Date(2019, 1, 1), Date(2018, 1, 1), false);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 2, 1), false);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 2), false);
    testCases.emplace_back(Date(2019, 1, 1, Date::US_LONG), Date(2019, 1, 1, Date::US_SHORT), true);

    std::cout << "TEST: equalDateValues() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = std::get<0>(test).equalDateValues(std::get<1>(test));
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the equalities operator overload returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_equalityOperator() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), true);
    testCases.emplace_back(Date(2019, 1, 1), Date(2018, 1, 1), false);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 2, 1), false);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 2), false);
    testCases.emplace_back(Date(2019, 1, 1, Date::US_LONG), Date(2019, 1, 1, Date::US_SHORT), false);

    std::cout << "TEST: equality operator (==) ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = std::get<0>(test) == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the method nextDay() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_nextDay() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 2), true);
    testCases.emplace_back(Date(2019, 1, 31), Date(2019, 2, 1), true);
    testCases.emplace_back(Date(2019, 12, 31), Date(2020, 1, 1), true);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), false);
    testCases.emplace_back(Date(2016, 2, 28), Date(2016, 2, 29), true);
    testCases.emplace_back(Date(2017, 2, 28), Date(2017, 3, 1), true);

    std::cout << "TEST: nextDay() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = std::get<0>(test).nextDay() == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the prefix increment operator returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_incrementPrefixOperator() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 2), true);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), false);

    std::cout << "TEST: increment operator (++prefix) ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = ++std::get<0>(test) == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the postfix increment operator returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_incrementPostfixOperator() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 2), false);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), true);

    std::cout << "TEST: increment operator (postfix++) ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = std::get<0>(test)++ == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the method previousDay() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_previousDay() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 01, 02), Date(2019, 01, 01), true);
    testCases.emplace_back(Date(2019, 02, 01), Date(2019, 01, 31), true);
    testCases.emplace_back(Date(2020, 01, 01), Date(2019, 12, 31), true);
    testCases.emplace_back(Date(2019, 01, 01), Date(2019, 01, 01), false);
    testCases.emplace_back(Date(2016, 02, 29), Date(2016, 02, 28), true);
    testCases.emplace_back(Date(2017, 03, 01), Date(2017, 02, 28), true);

    std::cout << "TEST: previousDay() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = std::get<0>(test).previousDay() == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the postfix decrement operator returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_decrementPostfixOperator() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 2), Date(2019, 1, 1), false);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), true);

    std::cout << "TEST: decrement operator (postfix--) ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        Date date = std::get<0>(test);
        int returnVal = date-- == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the prefix decrement operator returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_decrementPrefixOperator() {
    std::vector<std::tuple<Date, Date, bool>> testCases;
    testCases.emplace_back(Date(2019, 1, 2), Date(2019, 1, 1), true);
    testCases.emplace_back(Date(2019, 1, 1), Date(2019, 1, 1), false);

    std::cout << "TEST: decrement operator (--prefix) ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = --std::get<0>(test) == std::get<1>(test);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the istream extraction operator overload functions correctly with
 * good input.
 * @return True if all test cases pass.
 */
bool test_Date::test_istreamOperatorOverloadWithGoodInput() {
    std::vector<std::tuple<std::string, Date>> testCases;
    testCases.emplace_back("07/31/2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07-31-2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07.31.2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07/31/2019", Date(2019, 7, 31, Date::US_LONG));
    testCases.emplace_back("07-31-2019", Date(2019, 7, 31, Date::US_LONG));
    testCases.emplace_back("07.31.2019", Date(2019, 7, 31, Date::US_LONG));
    testCases.emplace_back("31/07/2019", Date(2019, 7, 31, Date::EU_SHORT));
    testCases.emplace_back("31-07-2019", Date(2019, 7, 31, Date::EU_SHORT));
    testCases.emplace_back("31.07.2019", Date(2019, 7, 31, Date::EU_SHORT));
    testCases.emplace_back("31/07/2019", Date(2019, 7, 31, Date::EU_LONG));
    testCases.emplace_back("31-07-2019", Date(2019, 7, 31, Date::EU_LONG));
    testCases.emplace_back("31.07.2019", Date(2019, 7, 31, Date::EU_LONG));

    std::cout << "TEST: istream operator overload (>>) GOOD INPUT ... ";

    bool allPassing = true;
    Date returnVal;
    Date actualVal;
    std::string dateString;
    for (auto test : testCases) {
        try {
            actualVal = std::get<1>(test);
            returnVal.setDateStringFormat(actualVal.getDateStringFormat());
            dateString = std::get<0>(test);
            std::stringstream ss(dateString);
            ss >> returnVal;


            if (!(returnVal == actualVal)) {
                if (allPassing) std::cout << "TEST FAILED.\n";
                std::cout << "String Value: " << dateString << " Date Created: "
                          << returnVal << "\n"
                          << "Format: " << actualVal.getDateStringFormat() << "\n"
                          << "Expected: " << actualVal << "\n";
                allPassing = false;
            }
        }
        catch (const std::invalid_argument &ex) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "String Value: " << dateString << " Date Created: "
                      << returnVal << "\n"
                      << "Format: " << actualVal.getDateStringFormat() << "\n"
                      << "Expected: " << actualVal << "\n"
                      << "Exception: " << ex.what() << "\n";
            allPassing = false;
        }
        catch (const std::out_of_range &ex) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "String Value: " << dateString << " Date Created: "
                      << returnVal << "\n"
                      << "Format: " << actualVal.getDateStringFormat() << "\n"
                      << "Expected: " << actualVal << "\n"
                      << "Exception: " << ex.what() << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the istream extraction operator overload functions correctly by
 * throwing exceptions with bad input.
 * @return True if all test cases pass.
 */
bool test_Date::test_istreamOperatorOverloadWithBadFormatInputThrowsException() {
    std::vector<std::tuple<std::string, Date>> testCases;
    testCases.emplace_back("07312019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07--31-2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("abcdefghjk", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07.31..019", Date(2019, 7, 31, Date::US_SHORT));

    std::cout << "TEST: istream operator overload (>>) Bad Format Input throws exception ... ";

    bool allPassing = true;
    Date returnVal;
    Date actualVal;
    std::string dateString;
    for (auto test : testCases) {
        try {
            actualVal = std::get<1>(test);
            returnVal.setDateStringFormat(actualVal.getDateStringFormat());
            dateString = std::get<0>(test);
            std::stringstream ss(dateString);
            ss >> returnVal;
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Exception not caught.\n"
                      << "String Value: " << dateString << " Date Created: "
                      << returnVal << "\n"
                      << "Format: " << actualVal.getDateStringFormat() << "\n"
                      << "Expected: Invalid Argument Exception\n";
            allPassing = false;
        }
        catch (const std::invalid_argument &ex) {
            // do nothing, we want to catch this
        }
        catch (const std::out_of_range &ex) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "WRONG EXCEPTION CATCH.\n"
                      << "String Value: " << dateString << " Date Created: "
                      << returnVal << "\n"
                      << "Format: " << actualVal.getDateStringFormat() << "\n"
                      << "Expected: " << actualVal << "\n"
                      << "Exception: " << ex.what() << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the istream extraction operator overload functions correctly by
 * throwing exceptions with bad input formatting input.
 * @return True if all test cases pass.
 */
bool test_Date::test_istreamOperatorOverloadWithInvalidFormatThrowsException() {
    std::vector<std::tuple<std::string, Date>> testCases;
    testCases.emplace_back("07/32/2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07-32-2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07.32.2019", Date(2019, 7, 31, Date::US_SHORT));
    testCases.emplace_back("07/32/2019", Date(2019, 7, 31, Date::US_LONG));
    testCases.emplace_back("07-32-2019", Date(2019, 7, 31, Date::US_LONG));
    testCases.emplace_back("07.32.2019", Date(2019, 7, 31, Date::US_LONG));
    testCases.emplace_back("32/07/2019", Date(2019, 7, 31, Date::EU_SHORT));
    testCases.emplace_back("32-07-2019", Date(2019, 7, 31, Date::EU_SHORT));
    testCases.emplace_back("32.07.2019", Date(2019, 7, 31, Date::EU_SHORT));
    testCases.emplace_back("32/07/2019", Date(2019, 7, 31, Date::EU_LONG));
    testCases.emplace_back("32-07-2019", Date(2019, 7, 31, Date::EU_LONG));
    testCases.emplace_back("32.07.2019", Date(2019, 7, 31, Date::EU_LONG));
    testCases.emplace_back("07-31--019", Date(2019, 7, 31, Date::US_SHORT));

    std::cout << "TEST: istream operator overload (>>) out of range throws exception ... ";

    bool allPassing = true;
    Date returnVal;
    Date actualVal;
    std::string dateString;
    for (auto test : testCases) {
        try {
            actualVal = std::get<1>(test);
            returnVal.setDateStringFormat(actualVal.getDateStringFormat());
            dateString = std::get<0>(test);
            std::stringstream ss(dateString);
            ss >> returnVal;
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Exception not caught.\n"
                      << "String Value: " << dateString << " Date Created: "
                      << returnVal << "\n"
                      << "Format: " << actualVal.getDateStringFormat() << "\n"
                      << "Expected: Invalid Argument Exception\n";
            allPassing = false;
        }
        catch (const std::out_of_range &ex) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "WRONG EXCEPTION CATCH.\n"
                      << "String Value: " << dateString << " Date Created: "
                      << returnVal << "\n"
                      << "Format: " << actualVal.getDateStringFormat() << "\n"
                      << "Expected: " << actualVal << "\n"
                      << "Exception: " << ex.what() << "\n";
            allPassing = false;
        }
        catch (const std::invalid_argument &ex) {
            // do nothing we want to catch these for this test
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the static method isLeapYear() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_static_isLeapYear() {
    std::vector<std::tuple<int, bool>> testCases;
    testCases.emplace_back(2016, true);
    testCases.emplace_back(2017, false);
    testCases.emplace_back(2012, true);
    testCases.emplace_back(2000, true);
    testCases.emplace_back(1900, false);
    testCases.emplace_back(1904, true);
    testCases.emplace_back(1800, false);
    testCases.emplace_back(1700, false);

    std::cout << "TEST: static isLeapYear() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int returnVal = Date::isLeapYear(std::get<0>(test));
        int actualVal = std::get<1>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the member method isLeapYear() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_member_isLeapYear() {
    std::vector<std::tuple<int, bool>> testCases;
    testCases.emplace_back(2016, true);
    testCases.emplace_back(2017, false);
    testCases.emplace_back(2012, true);
    testCases.emplace_back(2000, true);
    testCases.emplace_back(1900, false);
    testCases.emplace_back(1904, true);
    testCases.emplace_back(1800, false);
    testCases.emplace_back(1700, false);

    std::cout << "TEST: member isLeapYear() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        Date date(std::get<0>(test), 1, 1);
        bool returnVal = date.isLeapYear();
        bool actualVal = std::get<1>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Date 1: " << std::get<0>(test) << " Date 2: " << std::get<1>(test) << "\n"
                      << "Should return: " << ((actualVal)?"TRUE":"FALSE") << " Actual return value: " << ((returnVal)?"TRUE":"FALSE") << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the static method daysInMonth() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_static_daysInMonth() {
    std::vector<std::tuple<int, int, int>> testCases;
    testCases.emplace_back(2019, 1, 31);
    testCases.emplace_back(2019, 2, 28);
    testCases.emplace_back(2016, 2, 29);
    testCases.emplace_back(2019, 3, 31);
    testCases.emplace_back(2019, 4, 30);
    testCases.emplace_back(2019, 5, 31);
    testCases.emplace_back(2019, 6, 30);
    testCases.emplace_back(2019, 7, 31);
    testCases.emplace_back(2019, 8, 31);
    testCases.emplace_back(2019, 9, 30);
    testCases.emplace_back(2019, 10, 31);
    testCases.emplace_back(2019, 11, 30);
    testCases.emplace_back(2019, 12, 31);

    std::cout << "TEST: static daysInMonth() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int year = std::get<0>(test);
        int month = std::get<1>(test);
        int returnVal = Date::daysInMonth(year, month);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Year: " << year << " Month: " << month << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the member method isLeapYear() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_member_daysInMonth() {
    std::vector<std::tuple<int, int, int>> testCases;
    testCases.emplace_back(2019, 1, 31);
    testCases.emplace_back(2019, 2, 28);
    testCases.emplace_back(2016, 2, 29);
    testCases.emplace_back(2019, 3, 31);
    testCases.emplace_back(2019, 4, 30);
    testCases.emplace_back(2019, 5, 31);
    testCases.emplace_back(2019, 6, 30);
    testCases.emplace_back(2019, 7, 31);
    testCases.emplace_back(2019, 8, 31);
    testCases.emplace_back(2019, 9, 30);
    testCases.emplace_back(2019, 10, 31);
    testCases.emplace_back(2019, 11, 30);
    testCases.emplace_back(2019, 12, 31);

    std::cout << "TEST: member daysInMonth() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int year = std::get<0>(test);
        int month = std::get<1>(test);
        int day = 1;
        Date date(year, month, day);
        int returnVal = date.daysInMonth(month);
        int actualVal = std::get<2>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Year: " << year << " Month: " << month << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the static method getMonthName() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_static_getMonthName() {
    std::vector<std::tuple<int, std::string>> testCases;
    testCases.emplace_back(1, "January");
    testCases.emplace_back(2, "February");
    testCases.emplace_back(3, "March");
    testCases.emplace_back(4, "April");
    testCases.emplace_back(5, "May");
    testCases.emplace_back(6, "June");
    testCases.emplace_back(7, "July");
    testCases.emplace_back(8, "August");
    testCases.emplace_back(9, "September");
    testCases.emplace_back(10, "October");
    testCases.emplace_back(11, "November");
    testCases.emplace_back(12, "December");

    std::cout << "TEST: static daysInMonth() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int month = std::get<0>(test);
        std::string returnVal = Date::getMonthName(month);
        std::string actualVal = std::get<1>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Month val: " << month << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}

/**
 * Verifies the static method getMonthName() returns the correct information.
 * @return True if all test cases pass.
 */
bool test_Date::test_member_getMonthName() {
    std::vector<std::tuple<int, std::string>> testCases;
    testCases.emplace_back(1, "January");
    testCases.emplace_back(2, "February");
    testCases.emplace_back(3, "March");
    testCases.emplace_back(4, "April");
    testCases.emplace_back(5, "May");
    testCases.emplace_back(6, "June");
    testCases.emplace_back(7, "July");
    testCases.emplace_back(8, "August");
    testCases.emplace_back(9, "September");
    testCases.emplace_back(10, "October");
    testCases.emplace_back(11, "November");
    testCases.emplace_back(12, "December");

    std::cout << "TEST: member daysInMonth() ... ";

    bool allPassing = true;
    for (auto test : testCases) {
        int month = std::get<0>(test);
        Date date(2019, month, 1);
        std::string returnVal = date.getMonthName();
        std::string actualVal = std::get<1>(test);

        if (returnVal != actualVal) {
            if (allPassing) std::cout << "TEST FAILED.\n";
            std::cout << "Month val: " << month << "\n"
                      << "Should return: " << actualVal << " Actual return value: " << returnVal << "\n";
            allPassing = false;
        }
    }

    if (allPassing) {
        std::cout << "ALL PASSED\n";
    }

    return allPassing;
}
