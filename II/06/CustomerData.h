#ifndef CUSTOMERDATA_H
#define CUSTOMERDATA_H

#include "PersonData.h"

/**
 * \brief CustomerData contains information about a customer.
 * Derived from PersonData to contain information about a person.
 * Has member variables for storing a unique customer ID number and a boolean
 * for determining if the customer should receiving mailing list items.
 * Provides getters and setters for all variables.
 */
class CustomerData : public PersonData {
private:
    unsigned int customerNumber{};
    bool mailingList{};
public:

    CustomerData() = default;

    CustomerData(const std::string &lastName,
                 const std::string &firstName,
                 const std::string &address,
                 const std::string &city,
                 const std::string &state,
                 const std::string &zip,
                 const std::string &phone,
                 unsigned int customerNumber,
                 bool mailingList);

    CustomerData(const CustomerData &rhs) = default;

    CustomerData & operator=(const CustomerData &rhs);

    CustomerData(CustomerData &&rhs) noexcept = default;

    CustomerData & operator=(CustomerData &&rhs) noexcept = default;

    unsigned int getCustomerNumber() const;

    void setCustomerNumber(unsigned int customerNumber);

    bool isMailingList() const;

    void setMailingList(bool mailingList);

    ~CustomerData() = default;
};

#endif // CUSTOMERDATA_H
