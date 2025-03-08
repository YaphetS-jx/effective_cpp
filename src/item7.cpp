#include <iostream>

class TimeKeeper {
public: 
    TimeKeeper() {};
    ~TimeKeeper() {
        std::cout << "TimeKeeper destructor" << std::endl;
    };
};


class AtomicClock : public TimeKeeper {
public:
    ~AtomicClock() {
        std::cout << "AtomicClock destructor" << std::endl;
    };
};


class TimeKeeper2 {
public: 
    TimeKeeper2() {};
    virtual ~TimeKeeper2() {
        std::cout << "TimeKeeper2 virtual destructor" << std::endl;
    };
};

class AtomicClock2 : public TimeKeeper2 {
public: 
    ~AtomicClock2() {
        std::cout << "AtomicClock2 destructor" << std::endl;
    };
};

// TimeKeeper3 is an abstract class, can not be instantiated
class TimeKeeper3 {
public: 
    TimeKeeper3() {};
    virtual ~TimeKeeper3() = 0; // pure virtual destructor, must be defined in derived class
    virtual void print() = 0; // pure virtual function, must be defined in derived class
};

// Definition of the pure virtual destructor. It will always be called anyway in derived class
TimeKeeper3::~TimeKeeper3() {
    std::cout << "TimeKeeper3 destructor" << std::endl;
}
// no need to define the pure virtual function here, but it can be defined

class AtomicClock3 : public TimeKeeper3 {
public: 

    // Destructor is defined here, but it is not necessary, even it's pure virtual
    // override is not necessary here. even we add it here, it will not be an override and still call 2 destructors
    ~AtomicClock3() override  {
        std::cout << "AtomicClock3 destructor" << std::endl;
    };

    // override is necessary here for any other pure virtual function
    void print() override final {
        std::cout << "AtomicClock3 print" << std::endl;
    };

    // if add final here, it will not be possible to override this function in derived class
};

int main() {

    std::cout << "----------------- test -----------------" << std::endl;    
    // this will call both destructors
    AtomicClock *ac = new AtomicClock();
    delete ac;

    std::cout << "----------------- test -----------------" << std::endl;
    // this will only call TimeKeeper destructor
    TimeKeeper *tk = new AtomicClock();
    delete tk;

    std::cout << "----------------- test -----------------" << std::endl;
    // this will call both destructors
    AtomicClock2 *ac2 = new AtomicClock2();
    delete ac2;

    std::cout << "----------------- test -----------------" << std::endl;
    // this will call both destructors
    TimeKeeper2 *tk2 = new AtomicClock2();
    delete tk2;

    std::cout << "----------------- test -----------------" << std::endl;
    // this will call both destructors
    AtomicClock3 *ac3 = new AtomicClock3();
    ac3->print();
    delete ac3;

    return 0;
}
