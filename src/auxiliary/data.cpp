#include <iostream>
#include "data.hpp"

Data::Data(int x) : x(x) {}

void Data::print() const {
    std::cout << "x = " << x << std::endl;
}