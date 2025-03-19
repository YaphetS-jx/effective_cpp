#include <iostream>

/* In case of derived class template, the base class template is not instantiated.
   To refer to member functions of the base class template, 3 methods:
   1. use this->
   2. use Base<T>::
   3. use using Base<T>::function;

   Reason why C++ does not assume members in base class template:
   - All template class can have total template specialization, and we can not assume the actual interface of the base class. see item25.
   */

template <typename T>
class Person {
public:
    Person(const T& name) : name(name) {}
    void print() const {
        std::cout << "Person name = " << name << std::endl;
    }
protected:
    T name;
};

template <typename T>
class Student : public Person<T> {
public:
    Student(const T& name) : Person<T>(name) {}
    void study1() const {
        // below is invalid since name can not be found. followed by 3 different methods to fix it.
        // std::cout << "Student name = " << name << std::endl;

        // 1. use this->        
        std::cout << this->name << " is studying" << std::endl;
    }

    void study2() const {
        // 2. use Base<T>::        
        std::cout << Person<T>::name << " is studying" << std::endl;
    }
    
    // 3. use using declaration. (has to be outside member function)
    using Person<T>::name;
    void study3() const {
        std::cout << name << " is studying" << std::endl;
    }
};


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Student<std::string> s("John");
        s.print();
        s.study1();
        s.study2();
        s.study3();
    }
    return 0;
}