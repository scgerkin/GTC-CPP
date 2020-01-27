#include "Procedure.h"



Procedure::Procedure(const std::string &name, const std::string &date,
                     const std::string &practitionerName, const double &charge)
    : name(name), date(date), practitionerName(practitionerName),
    charge(charge) {}

Procedure::Procedure(const Procedure &obj) {
    this->name = obj.name;
    this->date = obj.date;
    this->practitionerName = obj.practitionerName;
    this->charge = obj.charge;
}

std::string Procedure::getName() {
    return this->name;
}

void Procedure::setName(const std::string &name) {
    this->name = name;
}

std::string Procedure::getDate() {
    return this->date;
}

void Procedure::setDate(const std::string &date) {
    this->date = date;
}

std::string Procedure::getPractitionerName() {
    return this->practitionerName;
}

void Procedure::setPractitionerName(const std::string &practitionerName) {
    this->practitionerName = practitionerName;
}

double Procedure::getCharge() {
    return this->charge;
}

void Procedure::setCharge(const double &charge) {
    this->charge = charge;
}

void Procedure::print() {
    std::cout << "Procedure name: " << this->name << "\n"
        << "Date: " << this->date << "\n"
        << "Practitioner: " << this->practitionerName << "\n"
        << "Charge: $" << std::setprecision(2) << std::showpoint << std::fixed
        << this->charge << "\n";
}

Procedure::~Procedure() {}
