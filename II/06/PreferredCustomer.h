#ifndef PREFERREDCUSTOMER_H
#define PREFERREDCUSTOMER_H

#include "CustomerData.h"

/**
 * \brief PreferredCustomer contains information about a Preferred Customer.
 * Provides a getter/setter for total purchased amount and a method to get
 * the discount level for the customer.
 */
class PreferredCustomer : public CustomerData {
private:
    double purchasesAmount;
    double discountLevel;
public:
    PreferredCustomer();

    explicit PreferredCustomer(const CustomerData &obj);

    PreferredCustomer(const CustomerData &obj, double purchasesAmount);

    PreferredCustomer(const std::string &lastName,
                      const std::string &firstName,
                      const std::string &address,
                      const std::string &city,
                      const std::string &state,
                      const std::string &zip,
                      const std::string &phone,
                      unsigned int customerNumber,
                      bool mailingList,
                      double purchasesAmount);

    PreferredCustomer(const PreferredCustomer &rhs) = default;

    PreferredCustomer & operator=(const PreferredCustomer &rhs) = default;

    PreferredCustomer(PreferredCustomer &&rhs) noexcept = default;

    PreferredCustomer & operator=(PreferredCustomer &&rhs) noexcept = default;

    double getPurchasesAmount() const;

    void setPurchasesAmount(double amount);

    void addPurchase(double amount);

    void removePurchase(double amount);

    double getDiscountLevel() const;

    ~PreferredCustomer() = default;
private:
    void setDiscountLevel();
};


#endif // PREFERREDCUSTOMER_H
