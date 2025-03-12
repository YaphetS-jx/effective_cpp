#include "item23_header1.hpp"
#include "item23_header2.hpp"

/*
   Higher encapsulation --> fewer things can see it --> higher flexibility in changing it.
   Thus, encapsulate as less as possible. Non-member, Non-friend function is better than
   member function.
*/

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    item23::Person p("Alice", 30);
    item23::printPersonInfo(p); // Calls the non-member function with encapsulated access
    return 0;
}