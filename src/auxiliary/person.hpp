#pragma once
#include <string>


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


// Non-member, non-friend function uses Person's public interface.
// It can work with any object that provides the expected interface without needing to break encapsulation.
inline void printPersonInfo(const Person& p) {
    std::cout << "Name: " << p.getName() << ", Age: " << p.getAge() << std::endl;
}