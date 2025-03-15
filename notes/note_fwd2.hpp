#pragma once
#include <iostream>

// Forward declaration of ClassA
class ClassA;

class ClassB {
public:
    void greet(ClassA& a); // Reference to ClassA (Forward declaration sufficient)
    void sayHi();
};
