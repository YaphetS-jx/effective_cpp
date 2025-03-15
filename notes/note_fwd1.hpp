#pragma once
#include <iostream>

// Forward declaration of ClassB
class ClassB;

class ClassA {
public:
    void showMessage(ClassB& b); // Reference to ClassB (Forward declaration sufficient)
    void sayHello();
};
