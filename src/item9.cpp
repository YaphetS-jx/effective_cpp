#include <iostream>


/* Don't call a virtual function inside a constructor and destructor
1. for derived class, the base class constructor is called first, then the derived class constructor is called.
2. if the virtual function is called inside the base class constructor, the derived member function is not yet 
   constructed, thus the base class member function is called, but it's a pure virtual function, thus wrong
3. Transaction::logTransaction() never exists but it is called in the constructor of Transaction
4. Transcation is first construted, then dynamically cast to BuyTransaction
5. Generally, this way will lead to a bad scenario where the function is called before constructed or without construction . 
 */

class Transaction {
public:
    Transaction() {
        // calling the pure virtual function inside a constructor is a bad idea
        // logTransaction();
    };
    virtual void logTransaction() const = 0; // pure virtual function
};

class BuyTransaction : public Transaction {
public:
    virtual void logTransaction() const {
        std::cout << "BuyTransaction" << std::endl;
    };
};



int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    BuyTransaction b;
    return 0;
}