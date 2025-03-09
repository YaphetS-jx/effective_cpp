#include <iostream>

class Singleton {
public:
    static Singleton const & instance() {
        static Singleton singleton;
        std::cout << "instance() called" << std::endl;
        return singleton;
    };
    ~Singleton(){
        std::cout << "destructor called" << std::endl;
    };
    // this has to be const since instance() returns const reference
    void print() const {
        std::cout << "print called" << std::endl;
    }
private:
    // delete ctor, so it can only be constructed using instance()
    Singleton() {
        std::cout << "ctor will never be called" << std::endl;
    };
    // delete copy ctor 
    Singleton(Singleton &) = delete;
    // delete copy assignment oeprator 
    Singleton operator=(Singleton &) = delete;
    // delete move ctor
    Singleton operator=(Singleton &&) = delete;
};

int main() {

    auto & s = Singleton::instance();
    // 2 ways to call print 
    s.print();
    Singleton::instance().print();

    /* Below is error: this is calling copy assignment operator which is deleted. */
    // auto s = Singleton::instance();

    return 0;
}



