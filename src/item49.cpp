#include <iostream>
#include <vector>

/* new-handle is a error-handling function called before operator new fails to allocate memory.
   it can be used to throw an exception, call an error-logging function, or even try to free up memory. 

   std::set_new_handler(new_handler nh) sets the new-handle function of void (*new_handler)()
   
   If operator new fails to allocate memory, a well-designed new-handler function must do one of the following:
   1. make more memory available 
   2. install a different new-handle if current handle is still unable to allocate memory
   3. deinstall the new-handle by calling std::set_new_handler(0) so taht operator new will throw an exception
   4. throw an exception of type std::bad_alloc or a derived type
   5. call the function abort or exit
   
   the new-handler thing is a basic mechanism for error handling in C++, which could be designed as a base class.
 */

#include "auxiliary/newHandler.hpp"

// curiously recurring template pattern CRTP

// Custom new-handler function
void customNewHandler() {
    std::cerr << "Memory allocation failed! Custom handler invoked." << std::endl;
}

class Widget : public NewHandlerSupport<Widget> {
public:
    // Constructor that takes a size parameter
    Widget(size_t size) : size(size) {
        data.resize(size);
        std::cout << "Widget created with size: " << size << std::endl;
    }

    // Destructor
    ~Widget() {
        std::cout << "Widget destroyed." << std::endl;
    }

private:
    size_t size;
    std::vector<int> data; // Vector to hold data of the specified size
};


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        try {
            Widget::set_new_handler(customNewHandler);
            Widget* w = new Widget(1000);
            delete w;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Caught bad_alloc: " << e.what() << std::endl;
        }
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        // I don't why customNewHandler is never called
        try {
            Widget::set_new_handler(customNewHandler);
            Widget* w = new Widget(10000000000L);
            delete w;
        } catch (const std::bad_alloc& e) {
            std::cerr << "Caught bad_alloc: " << e.what() << std::endl;
        }
    }
    return 0;
}