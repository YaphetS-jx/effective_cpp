#include <iostream>
#include <type_traits>
#include <utility> // For std::forward

// T&& allows for both lvalue and rvalue references
// when T is an lvalue reference, i.e. T = t&, T&& = t& && = t&, becomes an lvalue reference
// when T is an rvalue reference, i.e. T = t&&, T&& = t&& && = t&&, becomes an rvalue reference
// this is called reference collapsing
template <typename T>
void printReferenceType(T&& arg) {
    // Determine the type of the argument
    using ArgType = decltype(arg);
    
    // Print the type of the argument
    if constexpr (std::is_same_v<ArgType, T&>) {
        std::cout << "Argument is an lvalue reference." << std::endl;
    } else if constexpr (std::is_same_v<ArgType, T&&>) {
        std::cout << "Argument is an rvalue reference." << std::endl;
    } else {
        std::cout << "Argument is of unknown reference type." << std::endl;
    }
}

// A function that takes an argument and forwards it
// std::forward is used to forward the argument to the printReferenceType function
// std::forward<T>(arg) will return an lvalue reference if T is an lvalue reference, otherwise it will return an rvalue reference
// this is called perfect forwarding
template <typename T>
void forwardToPrint(T&& arg) {
    printReferenceType(std::forward<T>(arg)); // Forward the argument 

    // without std::forward, arg will be an lvalue reference
    // since arg is a variable defined in current scope, it is an lvalue
    // so printReferenceType(arg) will print "Argument is an lvalue reference."
    
    // printReferenceType(arg);
}

int main() {
    int x = 10;
    int& lvalueRef = x; // lvalue reference
    int&& rvalueRef = 20; // rvalue reference

    std::cout << "Passing lvalue reference:" << std::endl;
    forwardToPrint(lvalueRef); // Should print "Argument is an lvalue reference."

    std::cout << "Passing rvalue reference:" << std::endl;
    forwardToPrint(std::move(rvalueRef)); // Should print "Argument is an rvalue reference."    

    std::cout << "Passing an lvalue:" << std::endl;
    forwardToPrint(x); // Should print "Argument is an lvalue reference."    

    std::cout << "Passing an rvalue:" << std::endl;
    forwardToPrint(30); // Should print "Argument is an rvalue reference."    

    return 0;
}
