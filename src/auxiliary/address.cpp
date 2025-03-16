#include "address.hpp"
#include <iostream>

Address::Address(const std::string& street, const std::string& city, const std::string& state, const std::string& zip)
    : street(street), city(city), state(state), zip(zip) {}

void Address::print() const {
    std::cout << "Address: " << street << ", " << city << ", " << state << ", " << zip << std::endl;
}