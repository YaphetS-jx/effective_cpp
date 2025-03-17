#pragma once

namespace function_ptr {

// forward declaration
class GameCharacter;

int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
public:
    // function pointer type which takes a const GameCharacter& as argument and returns an int
    typedef int (*HealthCalcFunc)(const GameCharacter &);
    // ctor 
    GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthCalcFunc(hcf) {}
    // public interface
    int healthValue() const;
    // public setter for the function pointer
    void setHealthCalc(HealthCalcFunc hcf) {
        healthCalcFunc = hcf;
    }
private: 
    // private function pointer
    HealthCalcFunc healthCalcFunc;
};

class EvilBadGuy : public GameCharacter {
public:
    // ctor
    explicit EvilBadGuy(HealthCalcFunc hcf = defaultHealthCalc) : GameCharacter(hcf) {}
};

inline int additionalHealthCalc(const GameCharacter& gc) {
    return 12;
}


} // namespace function_ptr
