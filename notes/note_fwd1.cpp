#include "note_fwd1.hpp"
#include "note_fwd2.hpp"  // Required here for full definition of ClassB

void ClassA::showMessage(ClassB& b) {
    b.sayHi();  // Calls a method from ClassB
}

void ClassA::sayHello() {
    std::cout << "Hello from ClassA!" << std::endl;
}
