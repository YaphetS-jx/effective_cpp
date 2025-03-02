#include <iostream>


template<typename T>
inline const T& callWithMax(const T& a, const T& b) {
    return a > b ? a : b;
}

int main() {
#define CALL_WITH_MAX(a, b) ((a) > (b) ? (a) : (b))

    int a = 5, b = 0;

    // a is incremented twice
    std::cout << "CALL_WITH_MAX(a++, b++) = " << CALL_WITH_MAX(a++, b) << std::endl;
    std::cout << "a = " << a << ", b = " << b << std::endl;

    a = 5; b = 0;
    // a is incremented once
    std::cout << "CALL_WITH_MAX(++a, ++b) = " << CALL_WITH_MAX(++a, b+10) << std::endl;
    std::cout << "a = " << a << ", b = " << b << std::endl;

    // call inline function 
    a = 4; b = 2;
    std::cout << "callWithMax(" << a << "," << b << ") = " << callWithMax(a, b) << std::endl;
    return 0;
}