#include "Patient.h"

Patient::Patient(const std::string &firstName, const std::string &middleName,
                 const std::string &lastName, const std::string &address,
                 const std::string &city, const std::string &state,
                 const std::string &zipCode, const std::string &phoneNumber,
                 const std::string &emergencyContactName,
                 const std::string &emergencyContactPhone)
    : firstName(firstName), middleName(middleName), lastName(lastName),
    address(address), city(city), state(state), zipCode(zipCode),
    phoneNumber(phoneNumber), emergencyContactName(emergencyContactName),
    emergencyContactPhone(emergencyContactPhone)
{}

Patient::Patient(const Patient &obj) {
    this->firstName = obj.firstName;
    this->middleName = obj.middleName;
    this->lastName = obj.lastName;
    this->address = obj.address;
    this->city = obj.city;
    this->state = obj.state;
    this->zipCode = obj.zipCode;
    this->phoneNumber = obj.phoneNumber;
    this->emergencyContactName = obj.emergencyContactName;
    this->emergencyContactPhone = obj.emergencyContactPhone;
}

std::string Patient::getFirstName() {
    return this->firstName;
}

void Patient::setFirstName(const std::string &firstName) {
    this->firstName = firstName;
}

std::string Patient::getMiddleName() {
    return this->middleName;
}

void Patient::setMiddleName(const std::string &middleName) {
    this->middleName = middleName;
}

std::string Patient::getLastName() {
    return this->lastName;
}

void Patient::setLastName(const std::string &lastName) {
    this->lastName = lastName;
}

std::string Patient::getAddress() {
    return this->address;
}

void Patient::setAddress(const std::string &address) {
    this->address = address;
}

std::string Patient::getCity() {
    return this->city;
}

void Patient::setCity(const std::string &city) {
    this->city = city;
}

std::string Patient::getState() {
    return this->state;
}

void Patient::setState(const std::string &state) {
    this->state = state;
}

std::string Patient::getZipCode() {
    return this->zipCode;
}

void Patient::setZipCode(const std::string &zipCode) {
    this->zipCode = zipCode;
}

std::string Patient::getPhoneNumber() {
    return this->phoneNumber;
}

void Patient::setPhoneNumber(const std::string &phoneNumber) {
    this->phoneNumber = phoneNumber;
}

std::string Patient::getEmergencyContactName() {
    return this->emergencyContactName;
}

void Patient::setEmergencyContactName(const std::string &emergencyContactName) {
    this->emergencyContactName = emergencyContactName;
}

std::string Patient::getEmergencyContactPhone() {
    return this->emergencyContactPhone;
}

void Patient::setEmergencyContactPhone(const std::string &emergencyContactPhone) {
    this->emergencyContactPhone = emergencyContactPhone;
}

void Patient::print() {
    std::cout << "Patient Information:\n"
        << this->lastName << ", " << this->firstName << " " << this->middleName
        << "\n"
        << this->address << "\n"
        << this->city << ", " << this->state << " " << this->zipCode << "\n"
        << "Phone: " << this->phoneNumber << "\n"
        << "Emergency Contact: " << this->emergencyContactName << "\n"
        << "Emergency Phone:   " << this->emergencyContactPhone << "\n";
}

Patient::~Patient() {}
