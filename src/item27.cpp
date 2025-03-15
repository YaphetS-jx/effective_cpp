#include <iostream>

/* 4 ways to cast: 
   dynamic_cast:        only for polymorphic types (slow)
   static_cast:         non-polymorphic types, no type check
   const_cast:          cast "away" constness or volatileness
   reinterpret_cast:    cast pointer-to-member types
*/

class Base {
protected: // allow derived class to access
    int val;
public:
    Base(int v): val(v) {}
    virtual ~Base() = default;
    virtual void update() {val ++;}
    virtual void change(int v) { val = v; }
    virtual void print() const { std::cout << "Base::print(), val = " << val << std::endl; }
};

class Derived: public Base {
public:
    Derived(int v): Base(v) {}
    virtual void change(int v) override { val = v + 1; }
    virtual void update() override {
        static_cast<Base>(*this).update();  // temp Base will be created so update is not called at all        
        // static_cast<Base*>(this)->update(); // bug, infinite loop, it still calls Derived::update()
        val++;
    }
    virtual void print() const override { std::cout << "Derived::print(), val = " << val << std::endl; }
};


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Base b(1);
        Derived d(2);
        // Base pointer can point to both Base and Derived object
        Base* pb = &b; 
        pb->print();        
        pb = &d;
        pb->print();
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Base b(1);
        b.update();
        b.print();
        Derived d(1);
        d.update();
        d.print();
    }
    return 0;
}