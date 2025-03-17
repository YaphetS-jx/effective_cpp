#include "std_function.hpp"

namespace std_function {

// default function
int defaultHealthCalc(const GameCharacter& gc) {
    return 21;
}

// public interface
int GameCharacter::healthValue() const {
    return healthCalcFunc(*this);
}

// compatible function 
short calcHealthShort(const GameCharacter& gc) {
    return 23;
}

// member function
float GameLevel::health(const GameCharacter& gc) const {
    return 24;
}

} // namespace std_function