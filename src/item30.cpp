#include <iostream>
#include "auxiliary/inline.hpp"

/* Inline function can cause code bloat, so very short functions are prefered. 
   Member functions are inline by default if defined in header file. 
   Don't inline ctor and dtor, which are much larger than it appears. 
*/

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        // These 2 calls will be replaced by the inline function
        // 2 template instantiations will be generated
        // thus code bloat will happen
        std:: cout << "max(1, 2) = " << max(1, 2) << std::endl;
        std:: cout << "max(1.0, 2.0) = " << max(1.0, 2.0) << std::endl;
    }
    return 0;
}