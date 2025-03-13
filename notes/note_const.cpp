#include <iostream>

class Type {
public: 
    Type(int i) : i(i) {}
    int i;
};

int main() {

    std::cout << "----------------- test -----------------" << std::endl;
    {
        Type a(10);
        Type b(20);

        const Type * t = &a;
        // t->i = 30; // error: assignment of member ‘Type::i’ in read-only object
        std::cout << "t ptr to a const Type to a = " << t->i << std::endl;
        t = &b;
        std::cout << "t ptr to a const Type to b = " << t->i << std::endl;
    }

    std::cout << "----------------- test -----------------" << std::endl;
    {
        Type a(10);
        Type b(20);

        Type * const t = &a;
        t->i = 30;
        std::cout << "t const ptr to a Type to a = " << t->i << std::endl;
        // t = &b; // error: assignment of read-only variable ‘t’
        Type const * const tt = &b;
        // tt->i = 40; // error: assignment of member ‘Type::i’ in read-only object
        std::cout << "tt const ptr to a const Type to b = " << tt->i << std::endl;
        // tt = &a; // error: assignment of read-only variable ‘tt’
    }

    std::cout << "----------------- test -----------------" << std::endl;
    {
        Type a(10);
        Type b(20);

        const Type * const t = &a;
        const Type * const * tt = &t;

        std::cout << "tt const ptr to a const Type ptr to a = " << (*tt)->i << std::endl;
    }
  
    return 0;
}