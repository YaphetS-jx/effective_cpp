#include <iostream>
#include <memory>

// multiple inheritance: one class can inherit from multiple classes

namespace test1 {

class A {
public:
    void checkout() const {
        std::cout << "A::checkout" << std::endl;
    }
};

class B {
public: // even if it is private, the signature is still the same
    void checkout() const {
        std::cout << "B::checkout" << std::endl;
    }
};

// it doesn't matter if it's public or private inheritance, the signature is still the same
class C : public A, public B {}; 
} // namespace test1

/* Virtual inheritance is used to solve the "diamond problem" in multiple inheritance.
   When a class inherits from two classes that share a common base class, without virtual inheritance,
   the derived class would contain two copies of the base class's members.
   
   Virtual inheritance ensures only one copy of the base class exists.
   
   Example diamond hierarchy:
                 Person
              /          \
         Student       Employee 
              \          /
              Professor
*/

namespace test2 {

class Person {
public:
    Person(const std::string& n) : name(n) {}
    void identify() const {
        std::cout << "I am " << name << std::endl;
    }
protected:
    std::string name;
};

// Virtual inheritance
class Student : virtual public Person {
public:
    Student(const std::string& n) : Person(n) {}
    void study() const {
        std::cout << name << " is studying" << std::endl;
    }
};

class Employee : virtual public Person {
public:
    Employee(const std::string& n) : Person(n) {}
    void work() const {
        std::cout << name << " is working" << std::endl;
    }
};

// Without virtual inheritance, Professor would have two copies of Person
// With virtual inheritance, only one copy exists
class Professor : public Student, public Employee {
public:
    // Must explicitly call Person constructor because of virtual inheritance
    // here none of Person(n), Student(n), Employee(n) can be missing
    // All base classes must be initialized
    Professor(const std::string& n) : Person(n), Student(n), Employee(n) {}
    void teach() const {
        std::cout << name << " is teaching" << std::endl;
    }
};

} // namespace test2

namespace test3 {
// pure virtual class can not be instantiated
class Base {
public: 
    virtual ~Base() = default;
    virtual void identify() const = 0;
};

class Derived : public Base {
public:
    void identify() const override {
        std::cout << "Derived::identify" << std::endl;
    }
};
// use factory function to create an instance of Derived
std::unique_ptr<Base> createBase() {
    return std::make_unique<Derived>();
}

} // namespace test3

// one example where multiple inheritance is useful
#include "auxiliary/multiple_inheritance.hpp"

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test1;
        C c;
        // have to specify the class name to call the method since A::checkout and B::checkout share same signature
        c.A::checkout();
        c.B::checkout();        
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test2;
        Professor p("John");
        p.identify();
        p.study();
        p.work();
        p.teach();
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test3;
        std::unique_ptr<Base> base = createBase();
        base->identify();
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace multiple_inheritance;
        DatabaseID pid;
        Person p(pid);
        std::cout << p.name() << std::endl;
        std::cout << p.email() << std::endl;
    }
    return 0;
}