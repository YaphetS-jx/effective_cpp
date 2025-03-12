#pragma once
#include <iostream>
#include "item23_header1.hpp"

namespace item23{
    // Non-member, non-friend function uses Person's public interface.
    // It can work with any object that provides the expected interface without needing to break encapsulation.
    inline void printPersonInfo(const Person& p) {
        std::cout << "Name: " << p.getName() << ", Age: " << p.getAge() << std::endl;
    }
}