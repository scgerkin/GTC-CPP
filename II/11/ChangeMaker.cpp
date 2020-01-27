#include "ChangeMaker.h"
#include <algorithm>

/**
 * Default constructor.
 * Initializes the map we are to use for our denominations.
 */
ChangeMaker::ChangeMaker() {
    initDenominationValueNameMap();
}

/**
 * Creates a map of denominations and the quantity to return to a customer.
 * Each key represents the name of a denomination (ie "nickel") and each
 * value is the number of that denomination to return.
 * @param amountOwed The amount the customer owes us.
 * @param amountTendered The amount the customer gave to us.
 * @return A map of denominations and their quantity to give for change.
 * @throws NoChangePossible If the amount owed is more than the amount tendered.
 */
std::map<std::string, int> ChangeMaker::makeChange(int amountOwed,
                                                   int amountTendered) {
    if (amountOwed > amountTendered) {
        throw NoChangePossible(amountOwed - amountTendered);
    }
    initChangeMap();
    std::vector<int> changeList = makeChange(amountTendered - amountOwed);
    for (const auto &val : changeList) {
        changeMap.at(denominationValueNameMap.at(val)) += 1;
    }
    return changeMap;
}

/**
 * Creates a string representation of our change to be made.
 * Each denomination used is added to a new line of the string with the quantity
 * we are to use followed by the name of the denomination (ie "1 nickel").
 * @return A string containing the number of denominations to give as change.
 * @throws NoChangePossible if makeChange() function has not been called yet.
 */
std::string ChangeMaker::getChangeStr() {
    // exit early if we haven't tried to make change yet
    if (changeMap.empty()) {
        throw NoChangePossible(
                "No change has been made yet, cannot create string.");
    }

    std::string result;
    bool emptyBody = true;

    // add the denominations we used to the result in ascending order of value
    for (const auto &entry : denominationValueNameMap) {
        int quantDenom = changeMap.at(entry.second);
        if (quantDenom > 0) {
            emptyBody = false;
            result += std::to_string(changeMap.at(entry.second)) + " " +
                      entry.second + "\n";
        }
    }
    // if we didn't add anything to the result, return a message as such
    if (emptyBody) {
        result = "There is no change to be made.\n";
    }
        // otherwise add a header and return the result
    else {
        result = "Here is how you will make change for that:\n" + result;
    }
    return result;
}

/**
 * Internal starting point for makeChange algorithm.
 * Creates the lists we need to store information about the change we are to
 * make and then fills each list by calling the recursive function of the
 * same name.
 * @param changeAmt The amount of change we are to return.
 * @return A list of denominations (value) that is to be returned.
 */
std::vector<int> ChangeMaker::makeChange(int changeAmt) {
    std::vector<int> changeList; // empty list to start off
    std::vector<int> denominations = getDescOrderedDenominationList();
    makeChange(changeAmt, denominations, changeList);
    return changeList;
}

/**
 * Recursive function to determine the amount of change to return.
 * Given an amount of change, a list of denominations, and a list to place
 * each denomination used into, this function recurs until there is no more
 * change to be given.
 * Each pass through the function subtracts the highest denomination in the list
 * (if possible) from the change amount, then calls itself again with the amount
 * reduced by the value of the denomination used.
 * If a denomination cannot be used, the function is called again with the same
 * change amount but with the first denomination in the list absent.
 * @param changeAmt The amount of change to return.
 * @param denominationList A list of denomination (values) to use.
 * @param changeList The list of denominations we are to pull and return to the
 *                   customer.
 */
void ChangeMaker::makeChange(int changeAmt,
                             const std::vector<int> &denominationList,
                             std::vector<int> &changeList) {
    if (changeAmt == 0) {
        // base case
        // no change to be made
        // exit early and unwind our stack
        return;
    }
    // determine if we can use our highest current denomination
    if (changeAmt < denominationList[0]) {
        // if we cannot, we will call the function recursively using a new
        // list of denominations without the first denomination in our till
        makeChange(changeAmt,
                   std::vector<int>(denominationList.begin() + 1,
                                    denominationList.end()),
                   changeList);
    }
    else {
        // if we can, add that denomination to the list of change
        // and then recur using our change amount minus that denomination
        // amount, and the full list of denominations
        changeList.push_back(denominationList[0]);
        makeChange(changeAmt - denominationList[0],
                   std::vector<int>(denominationList.begin(),
                                    denominationList.end()),
                   changeList);
    }
}

/**
 * Initializes our map that contains the value : name for the currency to be used.
 */
void ChangeMaker::initDenominationValueNameMap() {
    denominationValueNameMap.insert(std::make_pair(2000, "$20 bill"));
    denominationValueNameMap.insert(std::make_pair(1000, "$10 bill"));
    denominationValueNameMap.insert(std::make_pair(500, "$5 bill"));
    denominationValueNameMap.insert(std::make_pair(100, "$1 bill"));
    denominationValueNameMap.insert(std::make_pair(25, "quarter"));
    denominationValueNameMap.insert(std::make_pair(10, "dime"));
    denominationValueNameMap.insert(std::make_pair(5, "nickel"));
    denominationValueNameMap.insert(std::make_pair(1, "penny"));
}

/**
 * Initializes our changeMap object.
 * Each key is the name value of a denomination in the till.
 * Each value is initialized as 0 to start off.
 */
void ChangeMaker::initChangeMap() {
    changeMap.clear();
    for (const auto &entry : denominationValueNameMap) {
        changeMap.insert(std::make_pair(entry.second, 0));
    }
}

/**
 * Creates a list (vector) of our denomination values.
 * It constructs the vector from our denominationValueNameMap.
 * The list is in descending order of value to work with our algorithm for
 * making change.
 * @return A vector containing our denomination values in descending order.
 */
std::vector<int> ChangeMaker::getDescOrderedDenominationList() {
    std::vector<int> list;
    for (const auto &entry : denominationValueNameMap) {
        list.push_back(entry.first);
    }
    // ordered map stores in ascending order but we want in descending
    std::reverse(list.begin(), list.end());
    return list;
}






