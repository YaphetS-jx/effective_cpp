#include <iostream>

/* Encapsulation level (high is good): private > protected = public!
   Use private members and member functions to provide getter and setter.  */

class AccessLevels {
public: 
    int getReadOnly() const {
        return readOnly;
    }

    void setReadWrite(int value) {
        readWrite = value;
    }

    int getReadWrite() const {
        return readWrite;
    }

    void setWriteonly(int value) {
        writeOnly = value;
    }

    void print() {
        std::cout << "noAccess: " << noAccess << std::endl;
        std::cout << "readOnly: " << readOnly << std::endl;
        std::cout << "readWrite: " << readWrite << std::endl;
        std::cout << "writeOnly: " << writeOnly << std::endl;
    }
private: 
    int noAccess;
    int readOnly = 0;
    int readWrite;
    int writeOnly;
};

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    AccessLevels al;
    al.setReadWrite(10);
    al.setWriteonly(5);
    al.print();
    return 0;
}