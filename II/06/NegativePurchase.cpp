#include "NegativePurchase.h"

/**
 * \brief Default constructor.
 * \param value Exceptional value used that is not valid.
 */
NegativePurchase::NegativePurchase(double value) : value(value) {}

/**
 * \brief Getter for value.
 * \return value.
 */
double NegativePurchase::getValue() const {
    return value;
}