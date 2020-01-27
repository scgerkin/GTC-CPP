#include "PreferredCustomer.h"
#include "NegativePurchase.h"

/**
 * \brief No argument constructor.
 * Sets member variables to 0.
 */
PreferredCustomer::PreferredCustomer()
    : purchasesAmount(0), discountLevel(0)
{}

/**
 * \brief Copy constructor.
 * Sets discount level on creation in case bad data was provided for original
 * object's discount level (this should never happen but this provides
 * additional safety).
 * \param obj object to use for construction.
 */
PreferredCustomer::PreferredCustomer(const CustomerData &obj)
    : CustomerData(obj), purchasesAmount(0), discountLevel(0)
{
    setDiscountLevel();
}

/**
 * \brief Constructor for converting a CustomerData object into a
 * Preferred Customer object.
 * Sets discount level after initializing with provided purchasesAmount.
 * \param obj CustomerData object to create new object from.
 * \param purchasesAmount value to initialize purchasesAmount with.
 */
PreferredCustomer::PreferredCustomer(const CustomerData &obj,
                                     double purchasesAmount)
    : CustomerData(obj), purchasesAmount(purchasesAmount), discountLevel(0)
{
    setDiscountLevel();
}



/**
 * \brief Full argument constructor.
 * Sets discount level after initializing all member variables and base class
 * variables.
 * \param lastName Customer's last name.
 * \param firstName Customer's first name.
 * \param address Customer's address.
 * \param city Customer's city.
 * \param state Customer's state.
 * \param zip Customer's zipcode.
 * \param phone Customer's phone number.
 * \param customerNumber Customer's unique ID number.
 * \param mailingList Boolean value for if the customer is on the mailing list.
 * \param purchasesAmount value to initialize purchasesAmount with.
 */
PreferredCustomer::PreferredCustomer(const std::string &lastName,
                                     const std::string &firstName,
                                     const std::string &address,
                                     const std::string &city,
                                     const std::string &state,
                                     const std::string &zip,
                                     const std::string &phone,
                                     const unsigned int customerNumber,
                                     const bool mailingList,
                                     double purchasesAmount)
    : CustomerData(lastName, firstName, address, city, state, zip, phone,
                   customerNumber, mailingList),
    purchasesAmount(purchasesAmount), discountLevel(0)
{
    setDiscountLevel();
}


/**
 * \brief Getter for purchasesAmount.
 * \return purchasesAmount.
 */
double PreferredCustomer::getPurchasesAmount() const {
    return purchasesAmount;
}

/**
 * \brief setter for purchasesAmount
 * \param amount amount to set purchasesAmount to.
 * \throws NegativePurchase exception if amount parameter is a negative value.
 */
void PreferredCustomer::setPurchasesAmount(double amount) noexcept (false) {
    if (amount < 0) {
        throw NegativePurchase(amount);
    }
    this->purchasesAmount = amount;
    setDiscountLevel();
}

/**
 * \brief Sets the discount for the object.
 */
void PreferredCustomer::setDiscountLevel() {
    discountLevel = 0.0;
    if (purchasesAmount >= 500) {
        discountLevel = 0.05;
    }
    if (purchasesAmount >= 1000) {
        discountLevel = 0.06;
    }
    if (purchasesAmount >= 1500) {
        discountLevel = 0.07;
    }
    if (purchasesAmount >= 2000) {
        discountLevel = 0.1;
    }
}

/**
 * \brief Getter for discountLevel
 * \return decimal value for percent discount.
 */
double PreferredCustomer::getDiscountLevel() const {
    return discountLevel;
}