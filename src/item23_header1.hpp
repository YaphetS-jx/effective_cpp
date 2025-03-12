#pragma once
#include <string>

namespace item23{

class Person {
    private:
        std::string name;
        int age;
    public:
        Person(const std::string& n, int a) : name(n), age(a) {}
        
        // Public interface to access encapsulated data
        std::string getName() const { return name; }
        int getAge() const { return age; }
    };
}