#ifndef MONTH_H
#define MONTH_H

#include <string>
#include <map>

/** Month class holds information about a month.
Per program requirements, holds a string representation of the month.
Also holds a number representation of the month (i.e. 7 for July).
Uses a static hash map object to hold onto the string value as map key and
the number value as the map value to allow quick lookup when determining
the correct name/number for a month.
Provides operator overloads for increment, decrement, and in/out streaming.
*/
class Month {
private:
    std::string name;
    int number;
    static std::map<std::string, int> mapOfMonthNameNumber;

public:
    Month();
    Month(const std::string &monthName);
    Month(const int &monthNumber);
    Month(const Month &obj);
    void setName(const std::string &monthName);
    void setNumber(const int &monthNumber);
    std::string getName();
    int getNumber();
    Month operator++();
    Month operator++(int);
    Month operator--();
    Month operator--(int);
    friend std::ostream & operator<<(std::ostream &stream, const Month &month);
    friend std::istream & operator>>(std::istream &stream, Month &month);
    ~Month();

private:
    void fillMap();
    void determineNumber();
    void determineName();
};

#endif // MONTH_H