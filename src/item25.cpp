#include <iostream>

/* std::swap follows the implementation as 
template<typename T>
void swap(T &a, T&b) {
    T temp = a;
    a = b;
    b = temp;
} 
This is inefficient for large types which is based on pimpl (pointer to implementation) idiom.

Need to design a exception-safety swap function for pimpl idiom.
Key: swap based on operations on built-in types (pointer under pimpl) are exception-safe.

*/


namespace item25{
// some implementation of pimpl idiom and saving large data
template<typename T>
class WidgetImpl {};

template<typename T>
class Widget {
public: 
    // ctor
    Widget() : pIml(new WidgetImpl<T>()) {};

    // copy ctor 
    Widget(const Widget &rhs) : pIml(new WidgetImpl<T>()) {
        // don't use this->pIml = rhs.pIml because it will copy the pointer only 
        *(this->pIml) = *(rhs->pIml);
    }
    // copy assignment
    Widget &operator=(const Widget &rhs) {
        // don't use this->pIml = rhs.pIml because it will copy the pointer only 
        *(this->pIml) = *(rhs->pIml);
    }

    // dtor 
    ~Widget() {
        delete pIml;
    }

    /* First, define a member function to swap. pIml is a private value, only accessible to member function  */
    void swap(Widget &other) {
        using std::swap;
        // here is fine. no need to swap actual data but only the pointer 
        swap(pIml, other.pIml);
        std::cout << "member swap is called" << std::endl;
    }
private: 
    WidgetImpl<T> *pIml;
};

/* Second, define a non-member swap function in the same namespace */
template<typename T>
void swap(Widget<T> &a, Widget<T> &b) {
    a.swap(b);
    std::cout << "non-member swap is called" << std::endl;
}

class Test {};

}

/* Third, if defining a class (not template class), define a total template specialization for std::swap */
namespace std {
    template<>
    void swap(item25::Test &a, item25::Test &b) {
        std::cout << "tts of std::swap is called" << std::endl;
    }
}

/* Below is invalid and won't work 
namespace std {
    template<typename T>
    void swap(item25::Widget<T> &a, item25::Widget<T> &b) {
        a.swap(b);
        std::cout << "std::swap is called" << std::endl;
    } 
}
*/



int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace item25;
        Widget<int> w1;
        Widget<int> w2;

        // add std namespace here for search of std::swap
        using std::swap;

        // swap w1 and w2
        swap(w1, w2);
    }

    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace item25;
        Test t1;
        Test t2;

        // add std namespace here for search of std::swap
        using std::swap;

        // swap t1 and t2
        swap(t1, t2);
    }
    
    return 0;
}