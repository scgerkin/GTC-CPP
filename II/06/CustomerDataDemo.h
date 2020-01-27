#ifndef CUSTOMERDATADEMO_H
#define CUSTOMERDATADEMO_H
#include "PreferredCustomer.h"

// function prototypes used by CustomerDataDemo.cpp
void constructCustomer(PreferredCustomer &);
std::string getStringField(const std::string &);
int getCustomerNumber();
bool getMailingListStatus();
void modifySales(PreferredCustomer &);
void displayPurchasesAmount(const PreferredCustomer &);
bool checkModifySalesAgain();

#endif // CUSTOMERDATADEMO_H