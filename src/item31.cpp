#include <iostream>
#include <string>
#include <memory>

/* 1. depend on declarations instead of definitions
 * 2. header files should exist in full and declaration-only forms
   2 different ways to do this:
   - handle classes 
   - interface classes

   Forward declaration is preferred because it reduces coupling and compile time.
   */

#include "auxiliary/date.hpp"
#include "auxiliary/address.hpp"

// test handle classes
// here only declare the handle, no link to the implementation
#include "auxiliary/person_handle.hpp"

// test interface classes
// here only declare the interface, no link to the implementation
#include "auxiliary/person_interface.hpp"

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace handle;
        Person p("John", Date(1990, 1, 1), Address("123 Main St", "Anytown", "CA", "12345"));
        p.print();
    }

    {
        using namespace interface;
        auto p = Person::create("John", Date(1990, 1, 1), Address("123 Main St", "Anytown", "CA", "12345"));
        p->print();
    }

    return 0;
}