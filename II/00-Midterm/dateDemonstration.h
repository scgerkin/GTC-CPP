#ifndef DATEDEMONSTRATION_H
#define DATEDEMONSTRATION_H

#include "Date.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

enum MENU_SELECTION {CHANGE_DATE, CHANGE_FORMAT, INCREMENT_DATE, DECREMENT_DATE, DAYS_BETWEEN, PERFORM_MATH, UNIT_TESTS, EXIT};

void demonstrateDateClass();
MENU_SELECTION displayMainMenu();
int getMenuSelection(int maxSelections);
void displayDate(const Date &date);
void changeDate(Date &date);
void handleBadDateInput(const Date &date);
std::vector<std::string> createValidInputStringDisplays(const Date &date);
void changeDateFormat(Date &date);
void displayCurrentDateFormat(const Date &date);
void displayChangeDateFormatMenu(Date &date);
void demonstrateDaysBetweenDates(const Date &date);
void demonstrateSubtractionOperator(const Date &date);

#endif //DATEDEMONSTRATION_H
