#include "CustomerData.h"



/**
 * \brief Full argument constructor.
 * \param lastName Customer's last name.
 * \param firstName Customer's first name.
 * \param address Customer's address.
 * \param city Customer's city.
 * \param state Customer's state.
 * \param zip Customer's zip code.
 * \param phone Customer's phone.
 * \param customerNumber Customer's unique ID number.
 * \param mailingList Boolean value for if customer is on mailing list. 
 */
CustomerData::CustomerData(const std::string &lastName,
                           const std::string &firstName,
                           const std::string &address,
                           const std::string &city,
                           const std::string &state,
                           const std::string &zip,
                           const std::string &phone,
                           const unsigned int customerNumber,
                           const bool mailingList)
    : PersonData(lastName, firstName, address, city, state, zip, phone),
    customerNumber(customerNumber), mailingList(mailingList)
{}

/**
 * \brief Copy assignment overload.
 * Creates a new object by calling the base class constructor and setting the
 * member variables.
 * \param rhs The object to copy.
 * \return *this with copied values.
 */
CustomerData& CustomerData::operator=(const CustomerData &rhs) {
    if (this != &rhs) {
        PersonData::operator=(rhs);
        this->customerNumber = rhs.customerNumber;
        this->mailingList = rhs.mailingList;
    }
    return *this;
}

/**
 * \brief Getter for customerNumber.
 * \return customerNumber.
 */
unsigned int CustomerData::getCustomerNumber() const {
    return customerNumber;
}

/**
 * \brief Setter for customerNumber.
 * \param customerNumber value to set customerNumber to.
 */
void CustomerData::setCustomerNumber(const unsigned int customerNumber) {
    CustomerData::customerNumber = customerNumber;
}

/**
 * \brief Getter for mailingList.
 * \return true if on mailing list.
 */
bool CustomerData::isMailingList() const {
    return mailingList;
}

/**
 * \brief Setter for mailing list.
 * \param mailingList true if customer is on mailing list.
 */
void CustomerData::setMailingList(const bool mailingList) {
    CustomerData::mailingList = mailingList;
}
