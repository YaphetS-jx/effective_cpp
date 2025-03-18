#include <iostream>

// class: explicit interface + runtime polymorphism for virtual functions 
// template: implicit interface + compile-time polymorphism 

// interface is explicitly defined in the class
// a Widget * can point to any derived class, and the virtual functions to be called are determined at runtime
class Widget {
public:
    virtual ~Widget() = default;
    virtual void draw() const = 0;
    virtual void draw(int x, int y) const = 0;
};

// interface is implicitly defined in the template
// we don't know exactly what's the interface of T, but we know that T has a size() method and a normalize() method
// for operator!= and operator>, we need to instantiate the template function with predefined types during compilation
template <typename T>
void doProcessing(T& w) {
    if (w.size() > 10 && w != someNastyWidget) {
        T temp(w);
        temp.normalize();
        temp.draw(0, 0);
    }
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    return 0;
}