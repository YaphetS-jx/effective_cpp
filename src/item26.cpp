#include <iostream>

class Widget {
public:
    int x;
    Widget(int x = 0) : x(x) {}
};

std::string somefunction(std::string str) {
    if (str.empty()) {        
        throw std::invalid_argument("str cannot be empty");
    }
    /* define a variable as long as possible until you know 
       the initialization argument of it. don't define it way earlier
       than needed.  */
    std::string encrypt(str);
    // do something with encrypt

    return encrypt;
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        somefunction("hello");

        // method 1
        // n ctor and n dtor called 
        for (int i = 0; i < 10; i++) {
            Widget w(i);
            // do something on w. 
        }

        // method 2
        // 1 ctor and 1 dtor called
        // n copy ctor called
        Widget w;
        for (int i = 0; i < 10; i++) {
            w = i;
            // do something on w. 
        }

        /* Prefer method 1 unless Widget is so large that ctor and dtor 
           take too much time. */
    }
    return 0;
}