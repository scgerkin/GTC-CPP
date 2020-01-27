#ifndef PROCEDURE_H
#define PROCEDURE_H

#include <iostream>
#include <iomanip>
#include <string>

/** Procedure class holds information about procedures.
A class named Procedure that has member variables for the following data:
- Name of the procedure
- Date of the procedure
- Name of the practitioner who performed the procedure
- Charges for the procedure

The Procedure class has a constructor that accepts an argument for each member
variable. The Procedure class also has getter and setter functions for each
member variable.
*/
class Procedure {
private:
    std::string name;
    std::string date;
    std::string practitionerName;
    double charge;
public:
    /** Default Procedure constructor.
    The default constructor (and only constructor besides a deep-copy) for the
    Procedure class.
    Requires all member variables to be initialized at instantiation.
    No implementation other than initializing the member variables.

    IMPORTANT:
    Input is not validated for null values or empty strings.

    @param name - The procedure name
    @param date - The date of the procedure
    @param practitionerName - The name of the practitioner who performed the
        procedure
    @param charge - The charges incurred for the procedure
    */
    Procedure(const std::string &name, const std::string &date,
              const std::string &practitionerName, const double &charge);

    /** Copy constructor.
    * Provides a deep copy of a Procedure object
    * @param obj - The Procedure object to be copied.
    */
    Procedure(const Procedure &obj);

    /** Getter for Procedure name. */
    std::string getName();

    /** Setter for Procedure name. */
    void setName(const std::string &name);

    /** Getter for Procedure date. */
    std::string getDate();
    
    /** Setter for Procedure date. */
    void setDate(const std::string &date);
    
    /** Getter for Procedure practitioner name. */
    std::string getPractitionerName();
    
    /** Setter for Procedure practitioner name. */
    void setPractitionerName(const std::string &practitionerName);
    
    /** Getter for Procedure charge. */
    double getCharge();
    
    /** Setter for Procedure charge. */
    void setCharge(const double &charge);

    /** Prints *this to the console. */
    void print();

    /** Destructor. No implementation needed during destruction. */
    ~Procedure();
};

#endif // !PROCEDURE_H