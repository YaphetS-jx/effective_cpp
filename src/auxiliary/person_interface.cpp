#include "person_interface.hpp"
#include "person_derive.hpp"

namespace interface {

std::shared_ptr<Person> 
Person::create(const std::string& name, const Date& birthday, const Address& addr) {
    // return the derived class object with same interface
    return std::make_shared<RealPerson>(name, birthday, addr);
    // this is wrong, can not instantiate the pure virtual class
    // return std::make_shared<Person>(new RealPerson(name, birthday, addr));
}

} // namespace interface