#include <iostream> 
#include <memory>


class Investment {
public:
    double val;
    Investment(double v = 1.) : val(v) {
        std::cout << "Investment constructor" << std::endl;
    };
    ~Investment() {
        std::cout << "Investment destructor" << std::endl;
    };
    void print() {
        std::cout << "Investment: " << val << std::endl;
    };
};

Investment* createInvestment(double v) {
    return new Investment(v);
}

void foo() {
    Investment *pInv = createInvestment(1.);
    /* Dangerous implementation!
    There can be many different cases where exceptions are thrown, so that delete pInv; is never reached!
    There can be sentences like return, break, etc added here, so that delete pInv; is never reached! 
    pInv might be a nullptr if constructor failed, then delete pInv leads to undefined behavior. */
    delete pInv;
}

int main() {

    std::cout << "----------------- test -----------------" << std::endl;
    /* Resource Acquisition Is Initialization (RAII) is a C++ programming idiom that ties the lifetime 
    of a resource that must be acquired before use to the lifetime of an object. it will automatically 
    delete the required resources when auto_ptr is destroyed (go out of scope). */
    {
        // auto_ptr is deprecated
        // std::auto_ptr<Investment> pInv(createInvestment(2.));
        // pInv->print();

        // unique_ptr is the best choice for single ownership
        std::unique_ptr<Investment> pInv2(createInvestment(2.));
        pInv2->print();

        // unique_ptr only supports single ownership, copy constructor and copy assignment operator are deleted
        // std::unique_ptr<Investment> pInv3 = pInv2; // error
        // std::unique_ptr<Investment> pInv4(pInv2); // error
    }
    
    std::cout << "----------------- test -----------------" << std::endl;
    /* Reference-counting Smart Pointer (RCSP) supports multiple ownerships and deletes the resources when
    nobody is pointing to it any longer.  */
    {
        // 2 different ways to create shared_ptr
        // single heap allocation, better performance, safer
        std::shared_ptr<Investment> pInv1 = std::make_shared<Investment>(3.);
        pInv1->print();
        // 2 heap allocations, worse performance, risk of memory leak if createInvestment throws exception
        std::shared_ptr<Investment> pInv2(createInvestment(4.));
        pInv2->print();        
        std::shared_ptr<Investment> pInv3(pInv2);
        pInv3.get()->val += 10;
        pInv2->print(); // now it's 14
    }

    std::cout << "----------------- test -----------------" << std::endl;
    /* shared_ptr and unique_ptr use default destructors of the type. 
    don't use them with dynamically allocated arrays, use std::vector instead. */
    {
        // below is worng, because the deleter of std::string is just delete, but we need delete[] for pointer to array
        // std::shared_ptr<std::string> aps(new std::string[10]);
        // we need to provide a custom deleter
        std::shared_ptr<std::string> aps(new std::string[10], [](std::string* p) {
            delete[] p;  // Correctly deletes the allocated array
            std::cout << "Array deleted\n";
        });

        aps.get()[0] = "Hello";
        aps.get()[1] = "World";
        std::cout << aps.get()[0] << " " << aps.get()[1] << std::endl;
    }
    return 0;
}