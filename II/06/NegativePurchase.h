#ifndef NEGATIVEPURCHASE_H
#define NEGATIVEPURCHASE_H

#include <exception>

/**
 * \brief Exception object for negative values entered in a purchase amount.
 * Contains the value that was used.
 */
class NegativePurchase : public std::exception {
private:
    double value;
public:
    explicit NegativePurchase(double value);

    double getValue() const;
};


#endif // NEGATIVEPURCHASE_H
