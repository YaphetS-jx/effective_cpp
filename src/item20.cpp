#include <iostream>
#include <memory>

/* Only use pass-by-value for built-in type and STL iterator and function object types! */

class Base {
public: 
    // has to declare const for the use of a const reference
    virtual void print() const{
        std::cout << "Base" << std::endl;
    }
    virtual ~Base() {
        std::cout << "Base destroyed" << std::endl;
    }
};

class Derived : public Base {
public: 
    // has to declare const for the use of a const reference
    void print() const override {
        std::cout << "Derived" << std::endl;
    }
    ~Derived() override {
        std::cout << "Derived destroyed" << std::endl;
    }
};

// pass by value
// problem of object slicing when pass a derived class object to a function that takes a base class object
void printBaseValue(Base b) {
    b.print();
    return;
}
// pass by reference to const
void printBaseRef(Base const &b) {
    b.print();
    return;
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    /* Prefer pass-by-reference-to-const to pass-by-value in most cases */
    {
        Base b;
        Derived d;
        // print base and dtor for temp value
        printBaseValue(b);
        // print base 
        printBaseRef(b);

        // print base and dtor for temp value
        // this is the error of object slicing
        printBaseValue(d);
        // print derived
        printBaseRef(d);

    }
    return 0;
}