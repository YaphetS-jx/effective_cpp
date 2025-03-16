#pragma once
#include <memory>
#include <string>
#include "fwd.hpp"

namespace interface {

class Person {
public:
    // factory function
    static std::shared_ptr<Person> 
    create(const std::string& name, const Date& birthday, const Address& addr);

    virtual ~Person() = default;
    virtual std::string name() const = 0;
    virtual Date birthDate() const = 0;
    virtual Address address() const = 0;
    virtual void print() const = 0;
};

} // namespace interface

