#include <iostream>
#include <memory>
#include <vector>

// Using serves: as 
// 1. Type Aliases (Modern alternative to typedef)
using IntPtr = std::unique_ptr<int>;
// it's equivalent to old style typedef
typedef std::unique_ptr<int> IntPtr;  

// 2. Bringing Names into Scope (Namespace aliasing) (Don't know why this is not working)
namespace MyNamespace {
    auto intPtr = IntPtr(new int(2));
}
// using mns = MyNamespace; // This is wrong
namespace mns = MyNamespace;

// 3. Template Aliases (For simplifying complex template types)
template<typename T>
using Vec = std::vector<T>;

// 4. Inheritance Control (When dealing with derived classes)
class Base {
public:
    // public member functions are visible in derived class
    void show() { std::cout << "Base::show()" << std::endl; } 
protected:
    // protected member functions can be brought into derived class's public interface by using `using` keyword
    // but it can not be called outside base class
    void log() { std::cout << "Base::log()" << std::endl; }
};

class Derived : public Base {
public:
    using Base::log;   // Brings `Base::log()` into `Derived`'s public interface
};

// Real world example for smart pointers
class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

using ResourceGuard = std::unique_ptr<Resource>;

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    std::cout << *(mns::intPtr.get()) << std::endl;

    std::cout << "----------------- test -----------------" << std::endl;
    Vec<int> v(3, 1);
    for(auto i : v) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::cout << "----------------- test -----------------" << std::endl;
    Derived d;
    d.show();
    d.log();

    // Base b;
    // b.log(); // error: 'void Base::log()' is protected within this context

    std::cout << "----------------- test -----------------" << std::endl;
    ResourceGuard rg(new Resource());

    return 0;
}