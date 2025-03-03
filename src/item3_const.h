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