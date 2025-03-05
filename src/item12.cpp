#include <iostream>


/* Don't forget new-added variabels and base class in customized 
   copy constructor and copy assignment operator.  */


class Customer {
public:
    Customer(const std::string & s) : name(s) {};
    Customer(const Customer& rhs) : name(rhs.name) {};
    Customer& operator=(const Customer& rhs) {
        name = rhs.name;
        return *this;
    };
    virtual void print() {
        std::cout << "Customer: name " << this->name << std::endl;
    };
private: 
    std::string name;
};


class PriorityCustomer: public Customer {
public: 
    PriorityCustomer(const std::string &s, int p) : 
        Customer::Customer(s),  // here Customer:: is unnecessary
        priority(p) {};

    PriorityCustomer(const PriorityCustomer& rhs) : 
        priority(rhs.priority), 
        Customer::Customer(rhs) {};

    PriorityCustomer& operator=(const PriorityCustomer &rhs) {
        priority = rhs.priority;
        Customer::operator=(rhs); // here Customer:: is necessary because there are 2 operator= in the class
        return *this;
    };
    void print() override {
        Customer::print(); // here Customer:: is necessary
        std::cout << "PriorityCustomer: priority " << this->priority << std::endl;
    };

private: 
    int priority;
};

int main() {

    Customer c1("c1");
    Customer c2 = c1;
    c2.print();

    PriorityCustomer pc1("pc1", 1);
    PriorityCustomer pc2 = pc1;
    pc2.print();   

    return 0;
}