#include <iostream>


/* Functions can have both auto as return type and -> as trailing return type.
   trailing return type -> is crucial when the return type depends on template 
   parameters or is difficult to express before the parameter list.  */

// trailing return type
template<typename T, typename U>
inline auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}

template<typename T, typename U>
auto minus(T t, U u) -> decltype(t + u) {
    return t - u;
}

// for template lambda functions, use auto for template 
// trailing return type is optional 
auto multiply = [](auto a, auto b) -> decltype(a * b) {
    return a * b;
};



int main() {
    std::cout << add(1, 2) << std::endl;
    std::cout << "type of add(1, 2): " << typeid(add(1, 2)).name() << std::endl;        // print i (GCC)
    std::cout << minus(1, 2.) << std::endl;
    std::cout << "type of minus(1, 2.): " << typeid(minus(1, 2.)).name() << std::endl;  // print d (GCC)
    std::cout << multiply(1, 2.) << std::endl;
    std::cout << "type of multiply(1, 2.): " << typeid(multiply(1, 2.)).name() << std::endl;  // print d (GCC)

    return 0;
}