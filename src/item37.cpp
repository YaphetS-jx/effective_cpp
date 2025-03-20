#include <iostream>
#include <memory>

/* For a pointer or reference, 2 different types. 
 * Static type: defined by the declaration of the pointer or reference
 * Dynamic type: defined by the type of the object to which the pointer or reference points
 * Statically bound functions (non-virtual functions) to be called depends on the static type of the pointer or reference
 * Dynamically bound functions (virtual functions) to be called depends on the dynamic type of the object
 * 
 * default argument values are statically bound, so if a derived class redefines a function that has a default argument, 
 * the default argument will be the one from the static type of the pointer or reference
 */

namespace test1 {

class Shape {
public:
    enum ShapeColor {Red, Green, Blue };
    virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle : public Shape {
public:
    // default argument value is statically bound, so this will call Shape::draw(Shape::Red)
    virtual void draw(ShapeColor color = Green) const override {
        std::cout << "Rectangle color: " << color << std::endl;
    };
};

class Circle : public Shape {
public:
    // this will override the default argument value of the base class, no default anymore 
    virtual void draw(ShapeColor color) const override {
        std::cout << "Circle color: " << color << std::endl;
    };
};

} // namespace test1

/* Keeping all default arguments to be the same for a virtual functions is hard. Change need to be made in all derived classes.
 * Use NVI (non-virtual interface) to avoid this problem. */

namespace test2 {
class Shape {
public:
    enum ShapeColor {Red, Green, Blue };
    // use a public non-virtual function to define the interface with default argument value
    void draw(ShapeColor color = Red) const {
        do_draw(color);
    }
    virtual ~Shape() = default;
private:
    virtual void do_draw(ShapeColor color) const = 0;
};

class Rectangle : public Shape {
private:
    virtual void do_draw(ShapeColor color) const override {
        std::cout << "Rectangle color: " << color << std::endl;
    };
};

class Circle : public Shape {
private:
    virtual void do_draw(ShapeColor color) const override {
        std::cout << "Circle color: " << color << std::endl;
    };
};
} // namespace test2

// example of virtual dtor
namespace test3 {
class Base {
public:
    virtual ~Base() {
        std::cout << "Base::~Base()" << std::endl;  
    }
};

class Derived: public Base {
public:
    virtual ~Derived() override {
        std::cout << "Derived::~Derived()" << std::endl;
    }
};


class Base1 {
public:
    ~Base1() {
        std::cout << "Base1::~Base1()" << std::endl;  
    }
};

class Derived1: public Base1 {
public:
    ~Derived1() {
        std::cout << "Derived1::~Derived1()" << std::endl;
    }
};
} // namespace test3

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test1;
        auto r = std::make_unique<Rectangle>();
        r->draw(); // this will call Rectangle::draw(Shape::Red), not Rectangle::draw(Shape::Green)
        auto c = std::make_unique<Circle>();
        c->draw(Shape::Blue); // this will call Circle::draw(Shape::Blue)
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test2;
        auto r = std::make_unique<Rectangle>();
        auto c = std::make_unique<Circle>();
        r->draw(); // this will call Shape::draw(Shape::Red)
        c->draw(); // this will call Shape::draw(Shape::Red)
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test3;        
        std::unique_ptr<Base> p = std::make_unique<Derived>(); // this will call both dtor
        std::unique_ptr<Base1> p1 = std::make_unique<Derived1>(); // this will only call Base1's dtor
    }

    return 0;
}