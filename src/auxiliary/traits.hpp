#pragma once
#include <iterator>

// using the iterator_traits in STL to implement advance
namespace traits{
    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d,
                std::random_access_iterator_tag)
    {
        std::cout << "random_access_iterator_tag\n";
        iter += d;
    }

    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d,
                std::bidirectional_iterator_tag)
    {
        std::cout << "bidirectional_iterator_tag\n";
        if (d >= 0) { while (d--) ++iter; }
        else { while (d++) --iter; }
    }

    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d,
                std::input_iterator_tag)
    {
        std::cout << "input_iterator_tag\n";
        if (d < 0 ) {
            throw std::out_of_range("Negative distance");
        }
        while (d--) ++iter;
    }

    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d,
                std::output_iterator_tag)
    {
        std::cout << "output_iterator_tag\n";
        if (d < 0 ) {
            throw std::out_of_range("Negative distance");
        }
        while (d--) ++iter;
    }

    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d,
                std::forward_iterator_tag)
    {
        std::cout << "forward_iterator_tag\n";
        if (d < 0 ) {
            throw std::out_of_range("Negative distance");
        }
        while (d--) ++iter;
    }

    // Important: typename is needed here！
    /* By adding typename before std::iterator_traits<IterT>::iterator_category, you inform the 
       compiler that iterator_category is a type. This is necessary because iterator_category is 
       dependent on the template parameter IterT, and the compiler needs to know that it should 
       treat it as a type.
    */
    template<typename IterT, typename DistT>
    void advance(IterT& iter, DistT d) {
        doAdvance(iter, d, typename std::iterator_traits<IterT>::iterator_category());
    }

    // when providing a argument, it will be treated as a variable, not a type. 
    // so we need to add typename to inform the compiler that iterator_category is a type.
}