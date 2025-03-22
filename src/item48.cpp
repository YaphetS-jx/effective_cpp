#include <iostream>
#include <list>
#include <iterator>
#include <typeinfo>

/* Template metaprogramming(TMP) is the process of writing template-based C++ programs that execute during compilation. 
   2 strengths:
   1. It makes some things easy that would otherwise be hard or impossible.
   2. TMP can shift work from runtime to compile-time.

   previous example: item 47
 */

void advance(std::list<int>::iterator& iter, int d)
{
    if (typeid(std::iterator_traits<std::list<int>::iterator>::iterator_category) ==
        typeid(std::random_access_iterator_tag)) {

        // iter += d; // <----- compilation error!!! even though this line will never be executed
    }
    else {
        if (d >= 0) { while (d--) ++iter; }
        else { while (d++) --iter; }
    }
}

// example of TMP doing loops by recursive template instantiation
template<unsigned n>
struct Factorial {
    enum { value = n * Factorial<n-1>::value };
};

template<>
struct Factorial<0> {
    enum { value = 1 };
};

/* 3 examples TMP can do 
   1. ensuring dimensional unit correctness
   2. optimizing matrix operations
   3. generating custom design pattern implementations */

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    std::cout << "Factorial<5>::value: " << Factorial<5>::value << std::endl;
    return 0;
}