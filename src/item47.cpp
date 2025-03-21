#include <iostream>

/* If you want to write a function advance to do iterator arithmetic, how do you implement it? */
namespace comments{
    template<typename IterT, typename DistT>
    void advance(IterT& iter, DistT d);
}
/* 5 STL iterator categories.
   1. Input iterators can move only forward, can move only one step at a time, can only read what they point to, 
      and can read what they’re pointing to only once. e.g. istream_iterators
   2. Output iterators are analogous, but for output: they move only forward, move only one step at a time, can 
      only write what they point to, and can write it only once. e.g. ostream_iterators
   3. Forward iterators can do everything input and output iterators can do, plus they can read or write what 
      they point to more than once. e.g. iterators for slist
   4. Bidirectional iterators add to forward iterators the ability to move backward as well as forward. 
      e.g. iterators for list, set, multiset, map, and multimap.
   5. Random access iterators add to bidirectional iterators the ability to perform “iterator arithmetic,” 
      i.e., to jump forward or backward an arbitrary distance in constant time. 
      e.g. iterators for vector, deque, and string are random access iterators. 
*/

namespace comments{
    // the tag hierarchy
    struct input_iterator_tag {};
    struct output_iterator_tag {};
    struct forward_iterator_tag: public input_iterator_tag {};
    struct bidirectional_iterator_tag: public forward_iterator_tag {};
    struct random_access_iterator_tag: public bidirectional_iterator_tag {};

    // containers always use nested typedef iterator_category to specify the iterator category
    template <typename T>
    class deque {
    public:
        class iterator {
        public:
            typedef random_access_iterator_tag iterator_category;
            // ...
        };
        // ...
    };

    template <typename T>
    class list {
    public:
        class iterator {
        public:
            typedef bidirectional_iterator_tag iterator_category;
            // ...
        };
        // ...
    };
}

// Implementation of advance depends on the iterator category. Thus, we need traits to get the iterator category at compile time.
namespace comments{
    // trait class 
    template<typename IterT>
    struct iterator_traits {
        using iterator_category = typename IterT::iterator_category;
    };
}

// with iterator_traits, we can implement advance by overloading so that the correct version is selected at compile time.
namespace comments{
    template<typename IterT, typename DistT>
    void advance(IterT& iter, DistT d) {
        doAdvance(iter, d, std::iterator_traits<IterT>::iterator_category());
    }

    // different implementations for different iterator categories    
    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d, std::random_access_iterator_tag) {
        iter += d;
    }

    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d, std::bidirectional_iterator_tag) {
        if (d >= 0) {
            while (d--) ++iter;
        } else {
            while (d++) --iter;
        }
    }

    template<typename IterT, typename DistT>
    void doAdvance(IterT& iter, DistT d, std::input_iterator_tag) {
        if (d < 0) {
            throw std::invalid_argument("Negative distance");
        }
        while (d--) ++iter;
    }
}   

// above are the ideas of iterator traits implemented in STL.
#include "auxiliary/traits.hpp"
#include <vector>
#include <list>
#include <unordered_set>

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {        
        std::vector<int> vec;
        std::list<int> lst;
        std::unordered_set<int> uset;

        auto vec_iter = vec.begin();
        traits::advance(vec_iter, 0);
        auto lst_iter = lst.begin();
        traits::advance(lst_iter, 0);
        auto uset_iter = uset.begin();
        traits::advance(uset_iter, 0);
    }
    return 0;
}