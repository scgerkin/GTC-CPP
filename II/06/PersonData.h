#ifndef PERSONDATA_H
#define PERSONDATA_H
#include <string>

/**
 * \brief PersonData contains data for a Person.
 * Provides getters and setters for each field.
 * All fields are strings for simplicity and require outside conversion if
 * necessary. This is to allow multiple formats for fields such as State that
 * could be in either the form 'GA' or 'Georgia'. Additionally, this allows
 * entry of zip codes that are full form (99999-9999) or simple form (99999).
 */
class PersonData
{
protected:
    std::string lastName;
    std::string firstName;
    std::string address;
    std::string city;
    std::string state;
    std::string zip;
    std::string phone;
public:
    PersonData();

    PersonData(const std::string &lastName,
               const std::string &firstName,
               const std::string &address,
               const std::string &city,
               const std::string &state,
               const std::string &zip,
               const std::string &phone);

    PersonData(const PersonData &rhs) = default;

    PersonData & operator=(const PersonData &rhs);

    PersonData(PersonData &&rhs) noexcept;

    PersonData & operator=(PersonData *rhs) noexcept;

    void setLastName(const std::string &lastName);

    const std::string &getFirstName() const;

    void setFirstName(const std::string &firstName);

    const std::string &getAddress() const;

    void setAddress(const std::string &address);

    const std::string &getCity() const;

    void setCity(const std::string &city);

    const std::string &getState() const;

    void setState(const std::string &state);

    const std::string &getZip() const;

    void setZip(const std::string &zip);

    const std::string &getPhone() const;

    void setPhone(const std::string &phone);

    const std::string &getLastName() const;

    ~PersonData() = default;
};

#endif // PERSONDATA_H
