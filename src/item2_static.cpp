#include <iostream>
#include "item2_static.h"


// can only define globally
const int A::y = 3;

int main() {
    
    A a(1);
    std::cout << "a.data = " << a.data << std::endl;
    // wrong 
    // std::cout << "a.x = " << a.x << std::endl;
    // correct
    std::cout << "A::x = " << A::x << std::endl;

    // wrong 
    // std::cout << "a.y = " << a.y << std::endl;

    // wrong, not defined
    // std::cout << "A::y = " << A::y << std::endl;

    // wrong, out-of-class definition must be at globe scope
    // const int A::y = 3;

    // can not call this before A::y is defined
    std::cout << "A::y = " << A::y << std::endl;
    return 0;
}