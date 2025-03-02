#include <iostream>
#include <string>


int main() {
    
    // const 
    std::string s1 = "aaa";
    std::string s2 = "bbb";

    const char *pc1 = &s1[0];
    
    char * const pc2 = &s2[0];
    
    // wrong, *pc1 is const 
    // *pc1 = "bbb";
    
    // change the ptr
    std::cout << "pc1 was " << *pc1 << std::endl;
    pc1 = &s2[0];
    std::cout << "pc1 is " << *pc1 << std::endl; // only print c, not ccc.

    // wrong pc2 is const
    // pc2 = tmp;

    // change the value
    std::cout << "pc2 was " << *pc2 << std::endl;
    *pc2 = 'c';
    std::cout << "pc2 is " << *pc2 << std::endl; // print ccc

    // print the string 
    std::cout << "s1 is " << s1 << std::endl;
    std::cout << "s2 is " << s2 << std::endl;

    return 0;
}