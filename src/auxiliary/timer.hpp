#pragma once
#include <iostream>

class Timer {
public:
    virtual void onTick() const {
        std::cout << "Timer tick" << std::endl;
    }
};