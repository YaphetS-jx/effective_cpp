#pragma once
#include <iostream>

class Mutex{};

// this is a RAII class that locks a mutex in its constructor and unlocks it in its destructor
class Lock{
public:
    explicit Lock(Mutex* pm) 
        : mitexpm(pm) {
        // lock the mutex
        lock(mitexpm);
    }

    ~Lock() {
        unlock(mitexpm);
    }

    // static method can be called without an instance of the class
    static void lock(Mutex* pm) {
        std::cout << "Locking the mutex" << std::endl;
    }
    static void unlock(Mutex* pm) {
        std::cout << "Unlocking the mutex" << std::endl;
    }

    // It's meaningless to copy a RAII class or object
    // delete copy constructor and copy assignment operator
    Lock(Lock& rhs) = delete;
    Lock& operator=(Lock& rhs) = delete;

private:
    Mutex* mitexpm;
};