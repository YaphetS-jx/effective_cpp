#include <iostream>

// exception propagation means that an exception thrown in a function can be caught in a function that calls it
// if no exception is caught, the program will terminate
void func2() {
    throw std::runtime_error("Error occurred!"); // Exception thrown
}

void func1() {
    func2(); // Exception propagates to func1
}

// If two identical exceptions are thrown, the second one is never reached because the first exception immediately starts unwinding the stack.
void func3() {
    throw std::runtime_error("Same Exception");
    throw std::runtime_error("Same Exception Again"); // Never executed
}

void exception_test() {
    try {
        func1(); // Exception propagates to main
    } catch (const std::exception &e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

// 2 exceptions propagating at the same time will terminate the program
void exception_test2() {
    try {
        // throw 1; // Exception thrown
        func2();

    // here catch is expecting a std::exception
    // if the exception thrown is an int like throw 1; then it will not be caught, thus terminate the program in next exception. 
    // for throw 1; the catch block should be catch (const int &e) or catch (...)
    } catch (const std::exception &e) {
        std::cout << "Caught exception 1: " << e.what() << std::endl;
    }
    try {
        // throw 2; // Exception thrown
        func2();
    } catch (const std::exception &e) {
        std::cout << "Caught exception 2: " << e.what() << std::endl;
    }
}


/* exception propagation in destructor
1. if an exception is thrown in a destructor, the program will terminate if the exception is not caught, 
   the memory will not be freed properly. 
2. whenever an exception is thrown, it will stop executing the codes after 
   the exception is thrown in current scope. 
3. Always wrap the exception in a try-catch block in the destructor to prevent the program from terminating.
4. Below code works, but if there is another exception thrown in the destructor, the program will terminate.
 */
class A {
public:
    bool flag; 
    A() : flag(false) {
        std::cout << "A constructor" << std::endl;
    }

    void close() {
        flag = true;
    }

    ~A() {
        try {
            if (!flag) {
                throw std::runtime_error("Error in destructor");
                // use cerr instead of throw exception
                // std::cerr << "Error in destructor" << std::endl;
            }
        } catch (...) {
            std::cout << "Exception caught in destructor" << std::endl;
            // std::cerr << "Warning: flag was not set before destruction!" << std::endl;
        }
        std::cout << "end of A destructor" << std::endl;
    }
};


/* Stack Unwinding
1. An exception is thrown: When an exception is thrown inside a function, normal execution stops.
2. Functions start to exit: The function that encountered the exception exits without completing.
3. Destructors are called: If any local objects were created in that function, their destructors 
   are automatically called before the function exits.
4. The stack unwinds to the caller: If the function doesn’t catch the exception, the exception 
   propagates to the function that called it.
5. Repeats until a handler is found: The process continues up the call stack until a try-catch 
   block is found. If no catch block is found, the program terminates (std::terminate() is called).
 */


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    // 1 exception propagating
    // meaning the exception thrown will keep propagating (finding the function calls it) until it is caught
    exception_test();
    
    std::cout << "----------------- test -----------------" << std::endl;
    // 2 exceptions propagating (not caught) at the same time will terminate the program
    exception_test2();

    // never use exception propagation in destructor
    // because if an exception is thrown in a destructor, the program will terminate
    A a;

    return 0;
}
