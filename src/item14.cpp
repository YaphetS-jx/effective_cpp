#include <iostream>
#include <memory> 
#include "auxiliary/mutex.hpp"

/* Functor is a functor (function object) in C++ is simply a class that overloads the operator() function, 
   allowing instances of the class to be used like a function. While classes are often used as containers
   for data and multiple methods, a functor encapsulates behavior and can store state while still being 
   callable like a function. Functor can be passed as a deleter!! */

class Multiply {
public: 
    Multiply(int v): val(v) {};
    ~Multiply() {};
    // key to a functor is that it overloads the operator() function
    int operator()(int x) const {
        return val * x;
    }
    Multiply(Multiply& rhs) = delete;
    Multiply& operator=(Multiply& rhs) = delete;
private:
    int val; 
};

class IntDeleter {
public:
    void operator()(int *p) {
        std::cout << "int deleter called!" << std::endl;
        delete p;
    }
};

int main() {

    std::cout << "----------------- test -----------------" << std::endl;
    // try RAII
    {
        Mutex m;
        Lock l(&m);
    }

    std::cout << "----------------- test -----------------" << std::endl;
    // try functor 
    {
        Multiply multiply2(2);
        Multiply multiply3(3);
        std::cout << "2 * 10 = " << multiply2(10) << std::endl;
        std::cout << "3 * 10 = " << multiply3(10) << std::endl;
    }
    
    std::cout << "----------------- test -----------------" << std::endl;
    // try functor as a deleter
    {
        // here new int(100) is only 1 int, initialized to 100
        // so the deleter should be default. 
        // new int[100] is an array of 100 ints, so the deleter should be an array deleter, which is delete[]
        std::unique_ptr<int, IntDeleter> p(new int(100));
    }

    return 0;
}