#ifndef CASHREGISTER_DEMONSTRATION_H
#define CASHREGISTER_DEMONSTRATION_H

#include "ChangeMaker.h"
#include <string>

/**
 * For demonstrating the ChangeMaker class.
 */
class Demonstration {
private:
    static const std::string QUIT; // string to signal user wants to exit.
    ChangeMaker changeMaker;
public:
    Demonstration() = default;
    ~Demonstration() = default;
    void start();

    class QuitException : public std::exception {
    public:
        QuitException() = default;
    };
private:
    void displayWelcomeMsg();
    void getMoney();
    void getMoreMoney(int owed, int tendered);
    void makeChange(int owed, int tendered);
    std::string getStringInput(const std::string &inputMsg);
    int getCurrency(const std::string &what);
    int convertCurrencyToInteger(double amt);
};

#endif //CASHREGISTER_DEMONSTRATION_H
