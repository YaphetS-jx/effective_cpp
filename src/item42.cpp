#include <iostream>
#include <vector>

/* class and typename are interchangeable in most cases.
   typename can not be omitted in cases of nested dependent types.
   Otherwise, the compiler treat it as a variable. 
   typename must not be used in the initialization list of base class.*/

// std::vector is a container while std::vector<T>::iterator is a type , which is a nested dependent type   
template <typename C> 
void print(const C& container) {
    typename C::const_iterator it = container.begin(); // typename is required here to indicate that C::const_iterator is a type
    for (; it != container.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

// can not use template directly with using or typedef. need to include a struct to make it work.
template <typename C>
struct ValueType {
    using type = typename std::iterator_traits<C>::value_type;
};

template <typename C>
using ValueType_t = typename ValueType<C>::type;

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        std::vector<int> v = {1, 2, 3, 4, 5};
        print<std::vector<int>>(v);
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        ValueType<std::vector<int>::iterator>::type v = 1;
        std::cout << "v = " << v << std::endl;
        std::cout << "type name = " << typeid(ValueType_t<std::vector<int>::iterator>).name() << std::endl; // i is for int
    }
    return 0;
}