#include "person_handle.hpp"
#include "person_impl.hpp" // this is for the member function of person_impl

// The implementation is separated from the declaration
// The implementation is in person_impl.cpp
// change in implementation won't affect the interface and clients

namespace handle {

std::string Person::name() const {
    return pImpl->name();
}

Date Person::birthDate() const {
    return pImpl->birthDate();
}

Address Person::address() const {
    return pImpl->address();
}

Person::Person(const std::string& name, const Date& birthday, const Address& addr)
    : pImpl(new PersonImpl(name, birthday, addr)) 
    {}

void Person::print() const {
    pImpl->print();
}

} // namespace handle