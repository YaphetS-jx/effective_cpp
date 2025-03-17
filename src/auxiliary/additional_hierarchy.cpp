#include "additional_hierarchy.hpp"

namespace additional_hierarchy {


int HealthCalcFunc::calc(const GameCharacter& gc) const {
    return 31;
}

int HealthCalcFuncDerived::calc(const GameCharacter& gc) const {
    return 32;
}

// use the other hierarchy to do calculation 
int GameCharacter::healthValue() const {
    return pHealthFunc->calc(*this);
}

} // namespace additional_hierarchy