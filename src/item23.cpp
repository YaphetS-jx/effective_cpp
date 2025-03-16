#include <iostream>
#include "auxiliary/person.hpp"

/*
   Higher encapsulation --> fewer things can see it --> higher flexibility in changing it.
   Thus, encapsulate as less as possible. Non-member, Non-friend function is better than
   member function.
*/

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    Person p("Alice", 30);
    printPersonInfo(p); // Calls the non-member function with encapsulated access
    return 0;
}