#include <iostream>

class Rational {
public: 
    // ctor allows implicit conversion from int to Rational
    Rational(int numerator = 0, int denominator = 1) : n(numerator), d(denominator) {}
    int numerator() const { return n; }
    int denominator() const { return d; }

    /* member function doesn't work in case  2 * rhs because it's equivlant to 
    2.operator*(rhs), while 2 has no class member function operator*. 
    But rhs * 2 works, because implicit conversion from 2 to Rational is valid. */
    
    // Rational operator*(const Rational &rhs) const {
    //     return Rational(n * rhs.n, d * rhs.d);
    // }
private: 
    int n, d;
};

// non-member operator* for Rational where implicit conversion is allowed for both operands
const Rational operator*(const Rational &lhs, const Rational &rhs) {
    return Rational(
        lhs.numerator() * rhs.numerator(), 
        lhs.denominator() * rhs.denominator()
    );
}


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    Rational oneEighth(1, 8);
    Rational oneHalf(1, 2);
    Rational result = oneHalf * oneEighth;
    std::cout << "oneHalf * oneEighth = " << result.numerator() << "/" << result.denominator() << std::endl;
    result = oneHalf * 2;
    std::cout << "oneHalf * 2 = " << result.numerator() << "/" << result.denominator() << std::endl;
    result = 2 * oneHalf;
    std::cout << "2 * oneHalf = " << result.numerator() << "/" << result.denominator() << std::endl;
    return 0;
}