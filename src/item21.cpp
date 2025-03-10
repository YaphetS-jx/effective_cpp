#include <iostream>

class Rational {
public: 
    Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {
        if (d == 0) throw std::invalid_argument("Denominator is zero");
    }

    // Never return a reference or pointer to a local object
    // just return a value instead 
    const Rational operator*(const Rational &rhs) const {
        return Rational(n * rhs.n, d * rhs.d);
    }

    void print() {
        std::cout << "Rational: " << n << "/" << d << std::endl;
    }

private: 
    int n, d;
};


// 2 methods below return reference and pointer to nothing, which is already destroyed
// Rational& operator*(const Rational &lhs, const Rational &rhs) {
//     // this is stack-allocated object
//     return Rational(lhs * rhs);
// }

// Rational* operator*(const Rational &lhs, const Rational &rhs) {
//     // this is heap-allocated object
//     return new Rational(lhs * rhs);
// }

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Rational a(1, 2), b(3, 4), c(5, 6);
        Rational d = a * b * c;
        d.print();
    }
    return 0;
}