#include "note_fwd1.hpp"
#include "note_fwd2.hpp"

int main() {
    ClassA a;
    ClassB b;

    std::cout << "Calling ClassA's method that interacts with ClassB:\n";
    a.showMessage(b);

    std::cout << "Calling ClassB's method that interacts with ClassA:\n";
    b.greet(a);

    return 0;
}
