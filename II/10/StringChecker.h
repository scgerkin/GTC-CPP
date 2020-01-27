#ifndef BALANCEPARENTHESES_STRINGCHECKER_H
#define BALANCEPARENTHESES_STRINGCHECKER_H

#include <string>
#include <iostream>
#include "List.h"

/**
 * Main class that contains the method for checking if a string of is balanced
 * with regards to parentheses. This is a utility class and not meant to be
 * instantiated. Additionally contains rudimentary unit testing that verifies
 * that the algorithm used to verify a string is working as intended.
 */
class StringChecker {
private:
    static const char LEFT = '(';
    static const char RIGHT = ')';
public:
    StringChecker() = delete; // utility class, do not instantiate

    /**
     * Iterates over a string to determine if the parentheses are balanced.
     * At each character, if the character is an opening parenthesis, it is
     * added to a stack.
     * If the character is a closing parenthesis, we attempt to get the most
     * recent character added to the stack.
     * If the stack is empty, the string is not balanced and we exit early.
     * If the character on top of the stack is an opening parenthesis, we
     * continue to iterate.
     * If the character in the string is not an opening or closing parenthesis,
     * we continue iterating and do nothing.
     * Finally, once we are done iterating through the string, if we have not
     * already exited early, we return whether or not the stack is empty.
     * If it is empty, the string is balanced. Otherwise, it is not.
     * @param str The string we want to check.
     * @return True if the string has balanced parentheses (or does not contain
     *         any).
     */
    static bool isBalanced(const std::string &str) noexcept {
        List stack;

        for (auto ch : str) {
            if (ch == LEFT) {
                stack.append(ch);
            }
            else if (ch == RIGHT) {
                try {
                    if (stack.popBack() != LEFT) {
                        return false;
                    }
                }
                catch (const List::EmptyList &ex) {
                    return false;
                }
            }
        }

        return stack.isEmpty();
    };
    
    /**
     * Rudimentary unit test for isBalanced().
     * Tests several good test cases and several bad test cases.
     */
    static void test_isBalanced() noexcept {
        std::string str = "()()()()()()()"; // good
        performTest(str, true);

        str = "(((((()())))))"; // good
        performTest(str, true);

        str = "(()(()))"; // good
        performTest(str, true);

        str = "a";
        performTest(str, true);

        str = "(a)"; // good
        performTest(str, true);

        str = "(a((a)a)a)"; // good
        performTest(str, true);

        str = "(\n)"; // good
        performTest(str, true);

        str = "(((()))"; // bad
        performTest(str, false);

        str = "()()()("; // bad
        performTest(str, false);

        str = ")("; // bad
        performTest(str, false);

        str = "(a("; // bad
        performTest(str, false);
    }
private:
    /**
     * Helper for performing a test.
     * Prints to screen status of test.
     * @param str The string we want to test against.
     * @param expectedResult The result we expect from the string.
     * @return Whether or not the test passed.
     */
    static bool performTest(const std::string &str, bool expectedResult) {
        std::cout << "Test on: \"" << str << "\" ...\n";
        if (isBalanced(str) == expectedResult) {
            std::cout << "Pass.\n";
            return true;
        }
        else {
            std::cout << "FAILURE!\n";
            return false;
        }
    }
};


#endif //BALANCEPARENTHESES_STRINGCHECKER_H
