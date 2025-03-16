#pragma once
#include <string>
#include <memory>
#include "fwd.hpp"
// requires date and address definitions 
// these are only needed to determine the size of PersonImpl class
#include "date.hpp"
#include "address.hpp"

namespace handle {

class PersonImpl {
public:
    PersonImpl(const std::string& name, const Date& birthday, const Address& addr);
    std::string name() const;
    Date birthDate() const;
    Address address() const;
    void print() const;
private:
    std::string name_;
    Date birthDate_;
    Address address_;
};

} // namespace handle