#include "note_fwd1.hpp"
#include "note_fwd2.hpp"  // Required here for full definition of ClassA

void ClassB::greet(ClassA& a) {
    a.sayHello();  // Calls a method from ClassA
}

void ClassB::sayHi() {
    std::cout << "Hi from ClassB!" << std::endl;
}
