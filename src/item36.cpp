#include <iostream>
#include <memory>

/* Never redefine an inherited non-virtual function, leading to inconsistent behavior 
   Virtual functions are dynamically bound, while non-virtual functions are statically bound.
   Statically  bound: compile-time resolution (function to be called is determined at compile time, the defined type of the object is used)
   Dynamically bound: runtime resolution (function to be called is determined at runtime, the actual type of the object is used)
*/


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