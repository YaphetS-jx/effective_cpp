#include <iostream>

/* aliasing of objects: pointer *px, px[i], reference &rf, value x, base class reference (see below) */
class Base {
public:
    virtual void display() const { 
        std::cout << "Base display" << std::endl;
    }
};

class Derived : public Base {
public:
    void display() const override {
        std::cout << "Derived display" << std::endl;
    }
};


class BitMap {};

class Widget {
public:
    Widget() {};
    ~Widget() {};
    Widget& operator=(const Widget& rhs);
    // some implementation to swap the content of two Widgets
    void swap(Widget& rhs) {};

private: 
    BitMap *pb;
};

/* unsafe implementation of operator= 

// if rhs == *this, it will delete pb and then try to copy it from itself
Widget& operator=(const WIdget& rhs) {
    delete pb;
    pb = new BitMap(*rhs.pb);
    return *this;
}

// new BitMap() might throw an exception, thus pb is deleted and nothing is returned
Widget& operator=(const Widget& rhs) {
    if (this == &rhs) return *this;
    delete pb;
    pb = new BitMap(*rhs.pb); 
    return *this;
}

// same as above, new might throw an exception, and pb is unchanged 
Widget& operator=(const Widget& rhs) {
    BitMap *pOrig = pb;
    pb = new BitMap(*rhs.pb);
    delete pOrig;
    return *this;
}
*/


/* safe implementation of operator= : copy and swap */
Widget& Widget::operator=(const Widget& rhs) {
    Widget temp(rhs); // copy rhs to temp
    swap(temp); // swap temp with *this
    return *this;
}

int main () {
    std::cout << "----------------- test -----------------" << std::endl;
    // base class reference refers to a derived class object
    Derived d;
    Base& b = d;
    // showing derived display
    b.display();

    return 0;
}