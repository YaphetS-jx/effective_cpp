#include <iostream>
#include "person_impl.hpp"


namespace handle {

std::string PersonImpl::name() const {
    return name_;
}

Date PersonImpl::birthDate() const {
    return birthDate_;
}

Address PersonImpl::address() const {
    return address_;
}

PersonImpl::PersonImpl(const std::string& name, const Date& birthday, const Address& addr)
    : name_(name), birthDate_(birthday), address_(addr) {
}

void PersonImpl::print() const {
    std::cout << "name: " << name_ << std::endl;
    birthDate_.print();
    address_.print();
}

} // namespace handle