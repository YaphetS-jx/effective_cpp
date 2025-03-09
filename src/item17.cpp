#include <iostream>
#include <memory>

/* store newed objects in standalone statement to avoid subtle resource leaks when exceptions are thrown! */

int priority() {
    // enable throw to test
    // throw std::runtime_error("priority() failed");
    return 1;
}

class Widget {};

void processWidget(std::shared_ptr<Widget> spw, int priority) {
    std::cout << "processWidget" << std::endl;
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    // 1. pass newed object directly
    processWidget(std::shared_ptr<Widget> (new Widget), priority());
    // if the compiler evaluates the priority() function call before calling ctor 
    // of std::shared_ptr<Widget>, the exception will be thrown before the newed object
    // which leads to a resource leak of the newed Widget

    // 2. save the newed object in a standalone statement first 
    // this way is safer in any case. 
    std::shared_ptr<Widget> spw(new Widget);
    processWidget(spw, priority());    

    return 0;
}