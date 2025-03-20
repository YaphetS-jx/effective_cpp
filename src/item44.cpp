#include <iostream>
#include <memory>

/* Code bloat in case of template class  */

// implementation 1
// pros: n is known at compile time, better for optimization in performance
// cons: code bloat, each instantiation of SquareMatrix will have its own copy of invert
template<typename T, std::size_t n>
class SquareMatrix {
public:
    SquareMatrix() : data(new T[n*n]) {}
    void invert() {
        std::cout << "SquareMatrix::invert" << std::endl;
    }
private: 
    std::unique_ptr<T[]> data; // use a smart pointer to manage the memory of data instead of chunk of memory on stack to avoid code bloat
    // has to be T[] for a T[nxn] array. Use std::vector<T> instead. 
};

// implementation 2
// pros: no code bloat, only one version of invert is needed for each type, almost no additional cost to call the base class version of invert
// pros: smaller object size, better for cache performance
// cons: no compile time optimization, the size of the matrix is known at runtime
template<typename T>
class SquareMatrixBase {
protected:
    SquareMatrixBase(std::size_t n) 
        : data(new T[n*n]), size(n) {}
    void invert() {
        std::cout << "SquareMatrixBase::invert" << std::endl;
    }
private:
    std::unique_ptr<T[]> data;
    std::size_t size;
};

template<typename T, std::size_t n>
class SquareMatrixDerived : private SquareMatrixBase<T> { // here typename is ignrored 
private: 
    using SquareMatrixBase<T>::invert; // expose the base class version of invert
public:
    SquareMatrixDerived(std::size_t size) 
        : SquareMatrixBase<T>(size) {}
    void invert() { SquareMatrixBase<T>::invert(); } // implicit inline call to use base class version of invert, almost 0 additional cost
    // can not use this->invert() here, leading to infinite loop
};

// other concerns: 
// typename will also cause code bloat. e.g. int and long share same binary representation, but different instantiation
// pass untyped pointer (void*) in function parameters instead of strongly typed pointer (int*) to avoid code bloat



int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        SquareMatrix<int, 10> sm1;
        sm1.invert();
        SquareMatrix<long, 10> sm2;
        sm2.invert();
        SquareMatrixDerived<int, 10> smd(10);
        smd.invert();
        SquareMatrixDerived<long, 10> smd2(10);
        smd2.invert();
    }
    return 0;
}