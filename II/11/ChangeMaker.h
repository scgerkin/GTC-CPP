#ifndef CASHREGISTER_CHANGEMAKER_H
#define CASHREGISTER_CHANGEMAKER_H

#include <vector>
#include <string>
#include <map>

/**
 * ChangeMaker is a utility class for making change given an amount owed and an
 * amount tendered by a customer.
 * The amounts given should be integer values of the lowest possible currency
 * denomination (ie $10.00 becomes 1000). The class uses a map of denomination
 * values and the names associated with them to determine how to make change
 * for a customer. Given that a customer purchases an item that costs $15.59,
 * and tenders $20.00 to us, we should return $4.41 in change.
 * This class will take that information and return a map of the bills and coins
 * to return to the customer (4 $1 bills, 1 quarter, 1 dime, 1 nickel, 1 penny).
 * The map returned is in ascending order of the name of the denomination.
 * As such, this class provides a getChangeStr() method that will return a
 * string representation of what we are to return with each denomination on a
 * new line.
 * Take care to first make change before calling this function or an exception
 * will be thrown.
 * An exception will also be thrown if the amount owed is greater than the
 * amount tendered.
 */
class ChangeMaker {
private:
    std::map<int, std::string> denominationValueNameMap;
    std::map<std::string, int> changeMap;
public:
    ChangeMaker();

    ~ChangeMaker() = default;

    /**
     * Class exception for handling invalid amounts.
     * This exception can result from attempting to make change when a customer
     * still owes us money (ie the item to buy costs $20.00 but they only give
     * us $10.00). It is also thrown if a call to getChangeStr() occurs before
     * making any change using makeChange().
     */
    class NoChangePossible : public std::runtime_error {
    public:
        explicit NoChangePossible(const std::string &msg)
                : std::runtime_error(msg) {}

        explicit NoChangePossible(int amountShort)
                : std::runtime_error(
                "Cannot make change, " + std::to_string(amountShort) +
                " is still owed.\n") {}
    };

    std::map<std::string, int> makeChange(int amountOwed, int amountTendered);

    std::string getChangeStr();

private:
    std::vector<int> makeChange(int changeAmt);

    void makeChange(int changeAmt, const std::vector<int> &denominationList,
                    std::vector<int> &changeList);

    void initDenominationValueNameMap();

    void initChangeMap();

    std::vector<int> getDescOrderedDenominationList();
};

#endif //CASHREGISTER_CHANGEMAKER_H
