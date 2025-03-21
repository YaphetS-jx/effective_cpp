#pragma once

namespace member_function {

    template <typename T>
    class Rational {
    public:
        Rational(const T& numerator = 0, const T& denominator = 1) : 
            num(numerator), den(denominator) {};
        const T numerator() const { return num; }
        const T denominator() const { return den; }
        void print() const {
            std::cout << num << "/" << den << std::endl;
        }
        const Rational operator*(const Rational& rhs) const {
            return Rational(num * rhs.numerator(), den * rhs.denominator());
        }
    private: 
        T num;
        T den;
    };
}


namespace friend_function {

    template <typename T>
    class Rational {
    public:
        Rational(const T& numerator = 0, const T& denominator = 1) : 
            num(numerator), den(denominator) {};
        const T numerator() const { return num; }
        const T denominator() const { return den; }
        void print() const {
            std::cout << num << "/" << den << std::endl;
        }
    private: 
        T num;
        T den;
    
    // friend function to link with non-member operator* so that T can be deduced
    // if it is defined outside class, then the compiler will throw undefined reference error 
    // this is implicit inline function, to avoid code bloat, define it outside class
    friend 
        const Rational operator*(const Rational& lhs, const Rational& rhs) {
            return doMultiply(lhs, rhs);            
        };
    };

    // outside definition is hidden 
    // template <typename T>
    // const Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs) {
    //     return Rational<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
    // }

    // actual implementation of operator*
    template <typename T>
    const Rational<T> doMultiply(const Rational<T>& lhs, const Rational<T>& rhs) {
        return Rational<T>(lhs.numerator() * rhs.numerator(), lhs.denominator() * rhs.denominator());
    }
}