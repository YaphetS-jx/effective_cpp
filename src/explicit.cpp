#include <iostream>

class A {
public:
    int x;
    // default constructor
    A(int y) : x(y) {                   // here int y = 0 is also okay
        this->x = y;
        std::cout << "default A constructor" << std::endl;
    }; 
    // destructor
    ~A() {
        std::cout << "A destructor called" << std::endl;
    };
};

class B {
public:
    int x;
    // default constructor
    explicit B(int x = 0, bool f = false) {
        this->x = x;
        std::cout << "defualt B constructor" << std::endl;
    };
    // destructor
    ~B() {
        std::cout << "B destructor called" << std::endl;
    };
};

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    A a1(2);
    std::cout << "a1 = " << a1.x << std::endl;

    // implicit conversion
    A a2 = 3;
    std::cout << "a2 = " << a2.x << std::endl;

    B b1(1, true);
    std::cout << "b1 = " << b1.x << std::endl;
    B b2(2);
    std::cout << "b2 = " << b2.x << std::endl;

    // B b3 = 3; Wrong. No implicit conversion

    B b3 = static_cast<B> (3);
    std::cout << "b3 = " << b3.x << std::endl;

    return 0;
}