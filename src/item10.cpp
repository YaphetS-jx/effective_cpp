#include <iostream>

/* Always return a reference (*this) for operators with assignment  */

class Rational {
public: 
    double val;
    Rational(double x = 0) {
        val = x;
    };
    ~Rational() {};

    Rational& operator=(const Rational& rhs) {
        val = rhs.val;
        return *this;
    }

    Rational& operator+=(const Rational& rhs) {
        val += rhs.val;
        return *this;
    }
};


int main() {
    Rational r1, r2;
    r1 = r2 = 3.5;
    std::cout << "r1: " << r1.val << std::endl;
    std::cout << "r2: " << r2.val << std::endl;
    
    return 0;
}