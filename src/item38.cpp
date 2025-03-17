#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

/* Application domain is used to modeling the problem to be solved. 
 * Implementation domain contains the implementation artifacts like mutex, buffers, search tree, etc.
 * 
 * Composition means has-a relationship in application domain.
 * Composition means is-implemented-in-terms-of relationship in implementation domain.
  */


// examples of is-implemented-in-terms-of relationship
// use list to implement a set
template<class T>
class Set {
public:
    bool member(const T& item) const {
        return std::find(rep.begin(), rep.end(), item) != rep.end();
    };
    void insert(const T& item) {
        if (!member(item)) 
            rep.push_back(item);
    };
    void remove(const T& item) {
        auto itr = std::find(rep.begin(), rep.end(), item);
        if (itr != rep.end())
            rep.erase(itr);
    };
    std::size_t size() const {
        return rep.size();
    };
    void print() const {
        for (const auto& item : rep) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    };
private: 
    std::list<T> rep;
};


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Set<int> s;
        s.insert(1);
        s.insert(2);
        s.insert(3);
        s.insert(3);
        s.print();
        s.remove(2);
        s.print();        
    }
    return 0;
}