#pragma once
#include <functional>

namespace std_function {

class GameCharacter;

int defaultHealthCalc(const GameCharacter& gc);

class GameCharacter {
public:
    // std::function instead of function pointer, flexible and powerful
    using HealthCalcFunc = std::function<int(const GameCharacter&)>;
    // ctor
    GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthCalcFunc(hcf) {}
    // public interface
    int healthValue() const;
    // public setter for the std::function
    void setHealthCalc(HealthCalcFunc hcf) {
        healthCalcFunc = hcf;
    }
private:
    HealthCalcFunc healthCalcFunc;
};


// other acceptable function objects
// functor 
class GameCharacterHealthFunc {
public:
    int operator()(const GameCharacter& gc) const {
        return 22;
    }
};

// compatible function 
short calcHealthShort(const GameCharacter& gc);

// member function
class GameLevel {
public:
    float health(const GameCharacter& gc) const;
};


} // namespace std_function