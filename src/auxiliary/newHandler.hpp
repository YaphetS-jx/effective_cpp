#pragma once
#include <new>

class NewHandlerHolder {
public: 
    explicit NewHandlerHolder(std::new_handler nh) : handler(nh) {}
    // restore the old new-handler when the object is destroyed
    ~NewHandlerHolder() { std::set_new_handler(handler); }

    // delete copy constructor and assignment operator
    NewHandlerHolder(NewHandlerHolder const &) = delete;
    NewHandlerHolder& operator=(NewHandlerHolder const &) = delete;

private: 
    std::new_handler handler;
};

// mixin style class? 
// this template is used to distinguish the new-handler support for different derived classes
template <typename T>
class NewHandlerSupport {
public: 
    static std::new_handler set_new_handler(std::new_handler p) {
        std::new_handler oldHandler = currentHandler;
        currentHandler = p;
        return oldHandler;
    }
    // custom new and delete operators have to be defined in pair 
    static void * operator new(std::size_t size) {
        // set the global new-handler as currentHandler
        NewHandlerHolder h(std::set_new_handler(currentHandler));
        // ::operator new is the global operator new
        return ::operator new(size);    
    }
    static void operator delete(void *ptr) noexcept {
        ::operator delete(ptr);
    }

private: 
    static std::new_handler currentHandler;
};


// initialize the currentHandler to nullptr
template <typename T>
std::new_handler NewHandlerSupport<T>::currentHandler = nullptr;