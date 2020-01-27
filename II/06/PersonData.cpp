#include <string>
#include <utility>
#include "PersonData.h"
#include <iostream>

/**
 * \brief No argument constructor initializes all member variables to empty
 * strings.
 */
PersonData::PersonData()
    : lastName(""), firstName(""), address(""), city(""), state(""), zip(""),
    phone("")
{}


/**
 * \brief Full argument constructor.
 * \param lastName Person's last name.
 * \param firstName Person's first name.
 * \param address Person's address.
 * \param city Person's city.
 * \param state Person's state.
 * \param zip Person's zipcode.
 * \param phone Person's phone number.
 */
PersonData::PersonData(const std::string &lastName,
                       const std::string &firstName,
                       const std::string &address,
                       const std::string &city,
                       const std::string &state,
                       const std::string &zip,
                       const std::string &phone)
    : lastName(lastName), firstName(firstName), address(address), city(city),
    state(state), zip(zip), phone(phone)
{}

/**
 * \brief Copy assignment operator overload.
 * \param rhs Object to copy
 * \return *this as copy of the object.
 */
PersonData& PersonData::operator=(const PersonData &rhs) {
    if (this != &rhs) {
        this->lastName = rhs.lastName;
        this->firstName = rhs.firstName;
        this->address = rhs.address;
        this->city = rhs.city;
        this->state = rhs.state;
        this->zip = rhs.zip;
        this->phone = rhs.phone;
    }
    return *this;
}

/**
 * \brief Move constructor.
 * \param rhs Object to move into new constructed object.
 */
PersonData::PersonData(PersonData &&rhs) noexcept {
    if (this != &rhs) {
        this->lastName = std::move(rhs.lastName);
        this->firstName = std::move(rhs.firstName);
        this->address = std::move(rhs.address);
        this->city = std::move(rhs.city);
        this->state = std::move(rhs.state);
        this->zip = std::move(rhs.zip);
        this->phone = std::move(rhs.phone);
    }
}

/**
 * \brief Move assignment overload.
 * \param rhs Object to move into *this.
 * \return *this with new, moved data.
 */
PersonData &PersonData::operator=(PersonData *rhs) noexcept {
    if (this != rhs) {
        this->lastName = std::move(rhs->lastName);
        this->firstName = std::move(rhs->firstName);
        this->address = std::move(rhs->address);
        this->city = std::move(rhs->city);
        this->state = std::move(rhs->state);
        this->zip = std::move(rhs->zip);
        this->phone = std::move(rhs->phone);
    }
    return *this;
}

/**
 * \brief Getter for lastName.
 * \return lastName.
 */
const std::string &PersonData::getLastName() const {
    return lastName;
}

/**
 * \brief Setter for lastName.
 * \param lastName new string to set lastName to.
 */
void PersonData::setLastName(const std::string &lastName) {
    PersonData::lastName = lastName;
}

/**
 * \brief Getter for firstName.
 * \return firstName.
 */
const std::string &PersonData::getFirstName() const {
    return firstName;
}

/**
 * \brief Setter for firstName.
 * \param firstName new string to set firstName to.
 */
void PersonData::setFirstName(const std::string &firstName) {
    PersonData::firstName = firstName;
}

/**
 * \brief Getter for address.
 * \return address.
 */
const std::string &PersonData::getAddress() const {
    return address;
}

/**
 * \brief Setter for address.
 * \param address new string to set address to.
 */
void PersonData::setAddress(const std::string &address) {
    PersonData::address = address;
}

/**
 * \brief Getter for city.
 * \return city.
 */
const std::string &PersonData::getCity() const {
    return city;
}

/**
 * \brief Setter for city.
 * \param city new string to set city to.
 */
void PersonData::setCity(const std::string &city) {
    PersonData::city = city;
}

/**
 * \brief Getter for state.
 * \return state.
 */
const std::string &PersonData::getState() const {
    return state;
}

/**
 * \brief Setter for state.
 * \param state new string to set state to.
 */
void PersonData::setState(const std::string &state) {
    PersonData::state = state;
}

/**
 * \brief Getter for zip.
 * \return zip.
 */
const std::string &PersonData::getZip() const {
    return zip;
}

/**
 * \brief Setter for zip.
 * \param zip new string to set zip to.
 */
void PersonData::setZip(const std::string &zip) {
    PersonData::zip = zip;
}

/**
 * \brief Getter for phone.
 * \return phone.
 */
const std::string &PersonData::getPhone() const {
    return phone;
}

/**
 * \brief Setter for phone.
 * \param phone new string to set phone to.
 */
void PersonData::setPhone(const std::string &phone) {
    PersonData::phone = phone;
}
