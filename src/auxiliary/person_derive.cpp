#include <iostream>
#include "person_derive.hpp"


namespace interface {

RealPerson::RealPerson(const std::string& name, const Date& birthday, const Address& addr)
    : name_(name), birthDate_(birthday), address_(addr) {}

std::string RealPerson::name() const {
    return name_;
}

Date RealPerson::birthDate() const {
    return birthDate_;
}

Address RealPerson::address() const {
    return address_;
}

void RealPerson::print() const {
    std::cout << "name: " << name_ << std::endl;
    birthDate_.print();
    address_.print();
}

} // namespace interface
