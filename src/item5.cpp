#include <iostream>
#include <vector>


class NamedObject {
public:
    // constructor. with user defined constructor, default constructor is not generated
    NamedObject(const char * name, const int value, std::vector<int> &vec) : nameValue(name), objectValue(value), vecRef(vec) {};

    // copy constructor
    // the default will fail because of reference of vector
    NamedObject(const NamedObject & rhs) : nameValue(rhs.nameValue), objectValue(rhs.objectValue), vecRef(rhs.vecRef) {};

    // copy assignment operator
    // the default will fail because of reference of vector
    NamedObject & operator= (const NamedObject & rhs) {
        if (this != &rhs) {
            nameValue = rhs.nameValue;
            objectValue = rhs.objectValue;
            vecRef = rhs.vecRef;
        }
        return *this;
    }

    // destructor
    ~NamedObject() {};

    // print 
    void print() {
        std::cout << "name: " << nameValue << ", object: " << objectValue << ", vector: ";
        for (auto & i : vecRef) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    std::vector<int> & vecRef;

private:
    std::string nameValue;
    int objectValue;
};

int main () {
    std::cout << "----------------- test -----------------" << std::endl;
    std::vector<int> vec = {1,2,3};    
    NamedObject no1("no1", 1, vec);
    no1.print();
    NamedObject no2 = no1;
    no2.print();
    NamedObject no3(no1);
    no3.vecRef[0] = 100;
    no3.print();
    // this will change vec in no1 because of reference
    no1.print();
    

    return 0;
}