#include <iostream>
#include <memory>

/* member function templates */
/* Assuming 3 level inheritance, Top -> Middle -> Bottom, see item 37 for using Top pointer to access Bottom object */
class Top {};
class Middle: public Top {};
class Bottom: public Middle {};

// A smart pointer class with the ability to handle all types of pointers
template <typename T>
class SmartPtr {
public:
    // default ctor 
    explicit SmartPtr(T* realPtr = nullptr) : ptr(realPtr) { std::cout << "default ctor" << std::endl; }
    // dtor
    ~SmartPtr() { std::cout << "dtor" << std::endl; }
    // copy ctor
    SmartPtr(const SmartPtr& other) : ptr(other.get()) { std::cout << "copy ctor" << std::endl; }
    // copy assignment operator
    SmartPtr& operator=(const SmartPtr& other) {
        ptr = other.get();
        std::cout << "copy assignment operator" << std::endl;
        return *this;
    }
    // get the raw pointer 
    T* get() const { return ptr; }

    /* Use member function templates to handle all types of pointers
       Use ptr(other.get()) to avoid unreasonable cast from U* to T* */
    // generalized copy ctor
    template <typename U>
    SmartPtr(const SmartPtr<U>& other) : ptr(other.get()) { std::cout << "generalized copy ctor" << std::endl; }
    // generalized copy assignment ctor 
    template <typename U>
    SmartPtr& operator=(const SmartPtr<U>& other) {
        ptr = other.get();
        std::cout << "generalized copy assignment ctor" << std::endl;
        return *this;
    }
private:
    T* ptr;
};

/* Notes: generalized copy ctor and normal copy ctor exist at the same time.
   Need to define them separately. */


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {        
        SmartPtr<Top> p1(new Top);
        // SmartPtr<Middle> p5(new Top); // this is invalid, Middle* = Top*
        SmartPtr<Top> p2(p1);
        SmartPtr<Top> p3;
        p3 = p2; // this is a copy assignment operator
        // SmartPtr<Top> p3 = p2; // this is not using copy assignment operator, but using copy ctor
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        SmartPtr<Top> p1(new Top);
        SmartPtr<Bottom> p2(new Bottom);        
        // SmartPtr<Middle> p2(p1); // this is invalid,  Middle*  = Top* (p1.get())
        // p2 = p1; // this is invalid, Bottom* = Top*
        SmartPtr<Top> p3(p2); // this is a generalized copy ctor
        p1 = p2; // this is a generalized copy assignment operator
    }
    return 0;
}