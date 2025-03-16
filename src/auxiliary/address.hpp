#pragma once
#include <string>
class Address {
public:
    Address(const std::string& street, const std::string& city, const std::string& state, const std::string& zip);
    Address(const Address& rhs) : street(rhs.street), city(rhs.city), state(rhs.state), zip(rhs.zip) {}
    Address& operator=(const Address& rhs) {
        street = rhs.street;
        city = rhs.city;
        state = rhs.state;
        zip = rhs.zip;
        return *this;
    }
    ~Address() {}
    void print() const;
private:
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
};