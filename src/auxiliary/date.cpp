#include <iostream>
#include "Date.hpp"

Date::Date(int y, int m, int d) : y_(y), m_(m), d_(d) {}

void Date::print() const {
    std::cout << "year = " << y_ << ", month = " << m_ << ", day = " << d_ << std::endl;
}