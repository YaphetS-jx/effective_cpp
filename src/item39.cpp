#include <iostream>
#include <memory>
#include "auxiliary/timer.hpp"

/* Private inheritance disables the implicit conversion to the base class.
   All members of the base class are private.
   Private inheritance means is-implemented-in-terms-of relationship.
   Interfaces are ignored while implementation is inherited.
*/

namespace test1 {
class Person {};
// student is not a person!
class Student : private Person {};

void eat(const Person& p) {
    std::cout << "eating" << std::endl;
}

void study(const Student& s) {
    std::cout << "studying" << std::endl;
}
} // namespace test1

/* Assuming we need to use a Timer on a Widget to do some counting. */
// Widget only needs the interface of Timer not the implementation, thus private inheritance is used.
// 2 issues for this implementation:
// 1. onTick can be declared public, which is against the design
// 2. Derived class of Widget can change the onTick behavior

namespace test2 {
class Widget : private Timer {
public:
    void Time() {onTick();}
private:
    void onTick() const override {
        std::cout << "Widget tick" << std::endl;
    }
};

} // namespace test2

/* public inheritance + composition. Derived class of Widget can not change the onTick behavior!
   Only use private inheritance when you must do
 */
namespace test3 {
class WidgetTimer : public Timer {
public:
    void onTick() const override {
        std::cout << "WidgetTimer tick" << std::endl;
    }
};

class Widget{
public:
    Widget() : timer(std::make_unique<WidgetTimer>()) {}
    void Time() {timer->onTick();}
private: 
    std::unique_ptr<WidgetTimer> timer;
};

} // namespace test3


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test1;
        Person p;
        Student s;
        eat(p);
        // eat(s); // error: 'Student' is not a 'Person'
        study(s);
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test2;
        Widget w;
        w.Time();
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace test3;
        Widget w;
        w.Time();
    }
    std::cout << "----------------- test -----------------" << std::endl;
    // test of EBO (Empty Base Optimization) Inheritance of Empty class does not add any size to the derived class.
    {
        class Empty {};
        class HoldAnInt {
            Empty e;
            int x;
        };
        class DerivedPrivate : private Empty {
            int x;
        };
        std::cout << sizeof(Empty) << std::endl; // = 1
        std::cout << sizeof(HoldAnInt) << std::endl; // = 8
        std::cout << sizeof(DerivedPrivate) << std::endl; // = 4
        std::cout << sizeof(int) << std::endl; // = 4
    }
    return 0;
}