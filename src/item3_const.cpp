#include <iostream>
#include <vector>
#include "item3_const.h"


// define operator outside class need to have 2 inputs 
Rational operator-(const Rational & lhs, const Rational & rhs) {
    return Rational(lhs.value - rhs.value);
};

int main() {
    
    /* const iterator */
    std::vector<int> v = {1,2,3,4,5};

    // const iterator
    const std::vector<int>::iterator it = v.begin();
    *it = 10; // Okay
    // it ++; // wrong because it is const iterator
    std::cout << "*it = " << *it << std::endl;

    // iterator of const 
    std::vector<int>::const_iterator cit = v.begin();
    // *cit = 10; // wrong because cit is iterator of const
    cit ++; // okay
    std::cout << "*cit = " << *cit << std::endl;

    /* const return value */
    Rational r1(2.0);
    Rational r2(3.0);

    Rational r3 = r1 * r2;
    std::cout << "r3 = " << r3.value << std::endl;
    r1 * r2 = r3; // okay, but meaningless
    Rational r4 = r1 + r2;
    std::cout << "r4 = " << r4.value << std::endl;
    // r1 + r2 = r4; // wrong because r1 + r2 is const

    // operator - outside class
    Rational r5 = r1 - r2;
    std::cout << "r5 = " << r5.value << std::endl;

    // operator[] const and non-const
    Text t("Hello");
    char c = t[0];
    std::cout << "t[0] = " << c << ", t.value = " << t.value << std::endl;
    const Text ct("World");
    c = ct[0];
    std::cout << "ct[0] = " << c << ", ct.value = " << ct.value << std::endl;

    // wouldn't work if return type is char instead of char&
    t[0] = 'h';
    std::cout << "text is " << t.text << std::endl;

    // test mutable
    Text2 t2(std::string("TEST"));    
    t2.print();
    c = t2[0];
    std::cout << "t2[0] = " << c << std::endl;
    c = static_cast<const Text2&>(t2)[1];
    std::cout << "const t2[1] = " << c << std::endl;
    
    return 0;
}