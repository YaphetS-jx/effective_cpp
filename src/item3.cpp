#include <iostream>
#include <vector>
#include <cstring>

class Rational {
public:
    double value;
    Rational(double x) : value(x) {};
    ~Rational() {};
    
    // always assume this is lhs, so at most 1 input
    Rational operator*(const Rational &rhs) {
        return Rational(this->value * rhs.value);
    };
    const Rational operator+(const Rational &rhs) {
        return Rational(this->value + rhs.value);
    };

    // this will be used first if defined in class before operator- defined outside class
    // Rational operator-(const Rational &rhs) {
    //     return Rational(this->value + rhs.value);
    // };
};

class Text {
public:
    std::string text;
    double value;
    Text(std::string s, double v = 0) : text(s), value(0) {};
    ~Text() {};

    // everything is const, can not be changed
    // first const is return type. Second const is the function itself
    // different return types (const or non-const) are the same for compiler
    const char& operator[] (std::size_t position) const {
        std::cout << "const operator[] called" << std::endl;
        // value = 1.;// wrong 
        return text[position];
    };

    char& operator[] (std::size_t position) {
        std::cout << "non-const operator[] called" << std::endl;
        value = 2.;// okay
        return text[position];
    };
};

class Text2 {
public:
    char *ptr;
    // without mutable, size() can not change length and lengthIsValid
    mutable std::size_t length;
    mutable bool lengthIsValid;
    
    Text2(std::string s) : ptr(s.data()), length(0), lengthIsValid(false) {};
    ~Text2() {};

    std::size_t size() const {
        if (!lengthIsValid) {
            length = std::strlen(ptr);
            lengthIsValid = true;
        }
        return length;
    }

    void print() const {
        this->size();
        std::cout << "length = " << length << std::endl;
        for (std::size_t i = 0; i < size(); ++i) {
            std::cout << ptr[i];
        }
        std::cout << std::endl;
    }

    const char& operator[] (std::size_t position) const {
        std::cout << "const operator[] called" << std::endl;
        if (position >= size()) {
            throw std::out_of_range("Text2::operator[]");
        }
        return ptr[position];
    };

    // call from const operator[]
    char& operator[] (std::size_t position) {
        std::cout << "non-const operator[] called" << std::endl;
        return const_cast<char&>( // remove const
            static_cast<const Text2&>(*this) // add const 
            [position]
        );
    };
};

// define operator outside class need to have 2 inputs 
Rational operator-(const Rational & lhs, const Rational & rhs) {
    return Rational(lhs.value - rhs.value);
};

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    /* const iterator */
    std::vector<int> v = {1,2,3,4,5};

    // const iterator
    const std::vector<int>::iterator it = v.begin();
    *it = 10; // Okay
    // it ++; // wrong because it is const iterator
    std::cout << "*it = " << *it << std::endl;

    // iterator of const 
    std::vector<int>::const_iterator cit = v.begin();
    // *cit = 10; // wrong because cit is iterator of const
    cit ++; // okay
    std::cout << "*cit = " << *cit << std::endl;

    std::cout << "----------------- test -----------------" << std::endl;
    /* const return value */
    Rational r1(2.0);
    Rational r2(3.0);

    Rational r3 = r1 * r2;
    std::cout << "r3 = " << r3.value << std::endl;
    r1 * r2 = r3; // okay, but meaningless
    Rational r4 = r1 + r2;
    std::cout << "r4 = " << r4.value << std::endl;
    // r1 + r2 = r4; // wrong because r1 + r2 is const

    // operator - outside class
    Rational r5 = r1 - r2;
    std::cout << "r5 = " << r5.value << std::endl;

    std::cout << "----------------- test -----------------" << std::endl;
    // operator[] const and non-const
    Text t("Hello");
    char c = t[0];
    std::cout << "t[0] = " << c << ", t.value = " << t.value << std::endl;
    const Text ct("World");
    c = ct[0];
    std::cout << "ct[0] = " << c << ", ct.value = " << ct.value << std::endl;

    // wouldn't work if return type is char instead of char&
    t[0] = 'h';
    std::cout << "text is " << t.text << std::endl;

    // test mutable
    Text2 t2(std::string("TEST"));    
    t2.print();
    c = t2[0];
    std::cout << "t2[0] = " << c << std::endl;
    c = static_cast<const Text2&>(t2)[1];
    std::cout << "const t2[1] = " << c << std::endl;
    
    return 0;
}