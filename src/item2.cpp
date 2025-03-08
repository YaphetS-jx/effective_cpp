#include <iostream>
#include <string>


// for macro test
template<typename T>
inline const T& callWithMax(const T& a, const T& b) {
    return a > b ? a : b;
}

#define CALL_WITH_MAX(a, b) ((a) > (b) ? (a) : (b))

// for static test
class A {
public:
    int data;
    explicit A(int x) : data(x) {};
    ~A() {};

    // both decalre and define in class
    static const int x = 1;

    // only declare in class
    static const int y;
};

// can only define globally
const int A::y = 3;

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    // const test
    {
        std::string s1 = "aaa";
        std::string s2 = "bbb";

        const char *pc1 = &s1[0];
        
        char * const pc2 = &s2[0];
        
        // wrong, *pc1 is const 
        // *pc1 = "bbb";
        
        // change the ptr
        std::cout << "pc1 was " << *pc1 << std::endl;
        pc1 = &s2[0];
        std::cout << "pc1 is " << *pc1 << std::endl; // only print c, not ccc.

        // wrong pc2 is const
        // pc2 = tmp;

        // change the value
        std::cout << "pc2 was " << *pc2 << std::endl;
        *pc2 = 'c';
        std::cout << "pc2 is " << *pc2 << std::endl; // print ccc

        // print the string 
        std::cout << "s1 is " << s1 << std::endl;
        std::cout << "s2 is " << s2 << std::endl;
    }

    std::cout << "----------------- test -----------------" << std::endl;
    // macro test
    {
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
    }
    
    std::cout << "----------------- test -----------------" << std::endl;
    // for static test
    {
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
    }

    return 0;
}