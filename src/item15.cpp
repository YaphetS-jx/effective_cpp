#include <iostream>
#include <memory>

class Investment {
public:
    double val;
    Investment(double v = 1.) : val(v), taxFree(true) {
        std::cout << "Investment constructor" << std::endl;
    };
    ~Investment() {
        std::cout << "Investment destructor" << std::endl;
    };
    void print() {
        std::cout << "Investment: " << val << ", taxFree: " << taxFree << std::endl;
    };
    bool taxFree;
    bool isTaxFree() const {
        return taxFree;
    };
};

Investment* createInvestment(double v) {
    return new Investment(v);
}

class FontHandle {};
class Font {
public: 
    FontHandle fh;
    // explicit constructor to avoid implicit conversion
    explicit Font(FontHandle fh) : fh(fh) {
        std::cout << "Font constructor" << std::endl;
    };
    ~Font() {
        std::cout << "Font destructor" << std::endl;
    };
    // explicit conversion function, requires calling getHandle() to get internal handle
    FontHandle getHandle() const {
        return fh;
    };
    // implicit conversion function, can directly use Font object to get internal handle    
    // This implicit conversion can lead to multiple copies of the raw handle without 
    // clear ownership semantics, thus increasing the risk of memory leak 
    operator FontHandle() const {
        return fh;
    };
    // Thus generally, explicit conversion function is preferred!!
};

void changeFont(FontHandle fh) {
    std::cout << "changeFont called" << std::endl;
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        std::shared_ptr<Investment> pInv(new Investment());
        /* To dereference the raw pointer of Investment, 3 different ways. */
        // 1. use get() to get raw pointer -- explicit conversion
        pInv.get()->print();
        // 2. use * to dereference the shared_ptr -- implicit conversion
        (*pInv).print();
        // 3. use -> to dereference the shared_ptr -- implicit conversion
        pInv->print();
    }

    std::cout << "----------------- test -----------------" << std::endl;
    {
        FontHandle fh;
        Font f(fh);
        // to use the internal handle of Font, 2 different ways
        // 1. use getHandle() to get internal handle -- explicit conversion
        changeFont(f.getHandle());
        // 2. use conversion function to get internal handle -- implicit conversion
        changeFont(f);
        // if we do a copy, it will increase the risk of memory leak
        FontHandle f2 = f;
        changeFont(f2); // to avoid warning. 
        // now internal FontHandle is owned by both f and f2, both of which can delete it
        // after either one deletes it, the other one becomes a dangling pointer
    }

    return 0;
}