#include <iostream>
#include <memory>

/* Three different level of inheritance of member functions:
 * 1. pure virtual function -- interface only (can have default implementation)
 * 2. simple virtual function -- interface + default implementation
 * 3. non-virtual function -- interface + mandatory implementation
 */

class Airport{};

// example 1: pure virtual function + mandatory implementation
class Airplane {
public:
    virtual ~Airplane() {};
    virtual void fly(const Airport& destination) = 0;
};

void Airplane::fly(const Airport& destination) {
    std::cout << "default fly" << std::endl;
}

class ModelA : public Airplane {
public:
    void fly(const Airport& destination) override {
        Airplane::fly(destination);
    }
};

class ModelB : public Airplane {
public:
    void fly(const Airport& destination) override {
        std::cout << "ModelB::fly" << std::endl;
    }
};

// example 2: simple virtual function + default implementation
class Airplane2 {
public:
    virtual ~Airplane2() {};
    virtual void fly(const Airport& destination) {
        defaultFly(destination);
    }

// protected  member function is only accessible to derived classes as a default implementation
// but it will be public in derived classes
protected:
    // default implementation of fly to avoid code duplication
    void defaultFly(const Airport& destination) {
        std::cout << "default fly" << std::endl;
    }
};

class ModelA2 : public Airplane2 {
public:
    void fly(const Airport& destination) override {
        Airplane2::defaultFly(destination);
    }
};

class ModelB2 : public Airplane2 {
public:
    void fly(const Airport& destination) override {
        std::cout << "ModelB2::fly" << std::endl;
    }
};


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        auto apA = std::shared_ptr<ModelA>(new ModelA());
        auto apB = std::shared_ptr<ModelB>(new ModelB());
        apA->fly(Airport());
        apB->fly(Airport());
    }

    std::cout << "----------------- test -----------------" << std::endl;
    {
        auto apA2 = std::shared_ptr<ModelA2>(new ModelA2());
        auto apB2 = std::shared_ptr<ModelB2>(new ModelB2());
        apA2->fly(Airport());
        apB2->fly(Airport());
    }
    return 0;
}