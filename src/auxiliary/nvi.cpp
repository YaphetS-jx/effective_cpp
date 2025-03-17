#include "nvi.hpp"

namespace nvi {

// this is the public interface
int GameCharacter::healthValue() const {
    return doHealthValue();
}

// this is the private implementation
int GameCharacter::doHealthValue() const {
    return 2;
}

// this is the private implementation in derived class
// which overrides the base class implementation
int EvilBadGuy::doHealthValue() const {
    return 1;
}

} // namespace nvi