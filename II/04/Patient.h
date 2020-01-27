#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

/**Patient class holds information about a patient.
A class named Patient that has member variables for the following data:
- First name, middle name, last name
- Address, city, state, and ZIP code
- Phone number

The Patient class has a constructor that accepts an argument for each member
variable. The Patient class also has getter and setter functions for each
member variable.
*/
class Patient {
private:
    std::string firstName;
    std::string middleName;
    std::string lastName;

    std::string address;
    std::string city;
    std::string state;
    std::string zipCode;

    std::string phoneNumber;

    std::string emergencyContactName;
    std::string emergencyContactPhone;
public:
    /** Default Patient constructor.
    The default constructor (and only constructor besides a deep-copy)
    for the Patient class.
    Requires all member variables to be initialized at instantiation.
    No implementation other than initializing the member variables.
    
    IMPORTANT:
    Input is not validated for null values or empty strings.
    
    @param firstName - The patient's first name
    @param middleName - The patient's middle name
    @param lastName - The patient's last name
    @param address - The patient's street address
    @param city - The patient's city of residence
    @param state - The patient's state of residence
    @param zipCode - The patient's zip code
    @param phoneNumber - The patient's phone number
    @param emergencyContactName - The name of the emergency contact for patient
    @param emergencyContactPhone - The phone number for patient emergency
        contact
    */
    Patient(const std::string &firstName, const std::string &middleName,
            const std::string &lastName, const std::string &address,
            const std::string &city, const std::string &state,
            const std::string &zipCode, const std::string &phoneNumber,
            const std::string &emergencyContactName,
            const std::string &emergencyContactPhone);

    /** Copy constructor.
    Provides a deep copy of a Patient object
    @param obj - The Patient object to be copied.
    */
    Patient(const Patient &); // copy construtor

    /** Getter for Patient first name. */
    std::string getFirstName();
    
    /** Setter for Patient first name. */
    void setFirstName(const std::string &firstName);
    
    /** Getter for Patient middle name. */
    std::string getMiddleName();
    
    /** Setter for Patient middle name. */
    void setMiddleName(const std::string &middleName);
    
    /** Getter for Patient last name. */
    std::string getLastName();
    
    /** Setter for Patient last name. */
    void setLastName(const std::string &lastName);

    /** Getter for Patient address. */
    std::string getAddress();

    /** Setter for Patient address. */
    void setAddress(const std::string &address);

    /** Getter for Patient city. */
    std::string getCity();

    /** Setter for Patient city. */
    void setCity(const std::string &city);

    /** Getter for Patient state. */
    std::string getState();

    /** Setter for Patient state. */
    void setState(const std::string &state);

    /** Getter for Patient zip code. */
    std::string getZipCode();

    /** Setter for Patient zip code. */
    void setZipCode(const std::string &zipCode);

    /** Getter for Patient phone number. */
    std::string getPhoneNumber();

    /** Setter for Patient phone number. */
    void setPhoneNumber(const std::string &phoneNumber);

    /** Getter for Patient emergency contact name. */
    std::string getEmergencyContactName();

    /** Setter for Patient emergency contact name. */
    void setEmergencyContactName(const std::string &emergencyContactName);

    /** Getter for Patient emergency contact phone number. */
    std::string getEmergencyContactPhone();

    /** Setter for Patient emergency contact phone number. */
    void setEmergencyContactPhone(const std::string &emergencyContactPhone);

    /** Prints *this to the console. */
    void print();

    /** Destructor. No implementation needed during destruction. */
    ~Patient();
};

#endif // !PATIENT_H
