#include <iostream>
#include <memory>

/* Never redefine an inherited non-virtual function, leading to inconsistent behavior */

class Base {
public: 
    void print() const {
        std::cout << "Base::print()" << std::endl;
    }
    // virtual destructor
    virtual ~Base() {
        std::cout << "Base::~Base()" << std::endl;
    };
};

class Derived : public Base {
public:
    // redefinition of the base class's print function
    void print() const {
        std::cout << "Derived::print()" << std::endl;
    }
    // virtual destructor
    virtual ~Derived() override {
        std::cout << "Derived::~Derived()" << std::endl;
    };
};
    

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Derived *pd = new Derived();
        Base *pb = pd;
        // this will call Base::print()
        pb->print();        
        // this will call Derived::print()
        pd->print();

        // this will call both dtors because Base::dtor is virtual 
        delete pb;
    }
    return 0;
}