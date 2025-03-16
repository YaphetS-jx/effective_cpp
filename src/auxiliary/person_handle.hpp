#pragma once
#include <string>
#include <memory>

// forward declaration of Data, Address, PersonImpl
#include "fwd.hpp"

namespace handle {

class Person {
public:
    Person(const std::string& name, const Date& birthday, const Address& addr);
    std::string name() const;
    Date birthDate() const;
    Address address() const;
    void print() const;
private:
    std::shared_ptr<PersonImpl> pImpl;
};

} // namespace handle