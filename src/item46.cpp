#include <iostream>
#include <memory>

/* template argument deduction only applies to functions, not class templates*/
namespace tad {
    template <typename T, typename U>
    void printPair(T first, U second) {
        std::cout << first << ", " << second << std::endl;
    }
}

/* 1. member functions can not support implicit type conversion for all parameters. see item 24
 * 2. implicit type conversion functions are never considered during template argument deduction.
 * 3. friend functions can support implicit type conversion for all parameters.
 * 4. friend functions doesn't automatically link with functions defined outside class, so need to define inside class
 * 5. friend functions are implicit inline functions, to avoid code bloat, define the main body outside class
 */
#include "auxiliary/template_rational.hpp"

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
     {
        // example of template argument deduction
        using namespace tad;
        printPair(1, 2.0); // this will automatically deduce T = int, U = double
     }

     std::cout << "----------------- test -----------------" << std::endl;
     {
        using namespace member_function;
        Rational<int> oneHalf(1, 2);
        oneHalf.print();
        // Rational<int> result = 2 * oneHalf; // this will fail because there is no operator* for int
        Rational<int> result = oneHalf * 2;
        result.print();
     }

     std::cout << "----------------- test -----------------" << std::endl;
     {
        using namespace friend_function;
        Rational<int> oneHalf(1, 2);
        oneHalf.print();
        Rational<int> result = oneHalf * 2; // work as expected
        result.print();
        result = 2 * oneHalf; // now if should work 
        result.print();
     }
    return 0;
}