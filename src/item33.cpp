#include <iostream>
#include <memory>

/* Names in derived classes hide names in base classes. Think about stack. 
   using declarations or forwarding functions can make hidden names visible. */

class Base {
public:
    virtual void mf1() = 0;
    virtual void mf1(int x) {
        std::cout << "Base::mf1(int), x =" << x << std::endl;
    };
    virtual void mf2() {
        std::cout << "Base::mf2()" << std::endl;
    };
    void mf3() {
        std::cout << "Base::mf3()" << std::endl;
    };
    void mf3(double x) {
        std::cout << "Base::mf3(double), x =" << x << std::endl;
    };
};

class Derived1 : public Base {
public:
    // mf1 and mf3 defined in Derived1 hide the all mf1 and mf3 in Base
    virtual void mf1() override {
        std::cout << "Derived1::mf1()" << std::endl;
    };
    void mf3() {
        std::cout << "Derived1::mf3()" << std::endl;
    };
    void mf4() {
        std::cout << "Derived1::mf4()" << std::endl;
    };
};


class Derived2 : public Base {
public:
    using Base::mf1;
    using Base::mf3;
    virtual void mf1() override {
        std::cout << "Derived2::mf1()" << std::endl;
    };
    void mf3() {
        std::cout << "Derived2::mf3()" << std::endl;
    };
    void mf4() {
        std::cout << "Derived2::mf4()" << std::endl;
    };
};



int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        auto d = std::make_unique<Derived1>();
        d->mf1();
        // d->mf1(5);  // Base::mf1(int) is hidden
        d->mf2(); // Base::mf2 is still visible because no mf2 defined in Derived1
        d->mf3();
        // d->mf3(3.14); // Base::mf3(double) is hidden   
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        auto d = std::make_unique<Derived2>();
        d->mf1();
        d->mf1(5);  // Base::mf1(int) is now visible
        d->mf2();
        d->mf3();
        d->mf3(3.14); // Base::mf3(double) is now visible   
    }
    return 0;
}