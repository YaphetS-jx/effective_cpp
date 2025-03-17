#include "function_ptr.hpp"

namespace function_ptr {

int defaultHealthCalc(const GameCharacter& gc) {
    return 11;
}

int GameCharacter::healthValue() const {
    return healthCalcFunc(*this);
}

} // namespace function_ptr