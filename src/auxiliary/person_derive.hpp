#pragma once

#include "person_interface.hpp"
#include "date.hpp"
#include "address.hpp"

namespace interface {

class RealPerson : public Person {
public:
    RealPerson(const std::string& name, const Date& birthday, const Address& addr);
    std::string name() const override;
    Date birthDate() const override;
    Address address() const override;
    void print() const override;
private:
    std::string name_;
    Date birthDate_;
    Address address_;
};

} // namespace interface