#pragma once
#include <string>
class Address {
public:
    Address(const std::string& street, const std::string& city, const std::string& state, const std::string& zip);
    void print() const;
private:
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
};