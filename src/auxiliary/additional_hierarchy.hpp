#pragma once

namespace additional_hierarchy {

// forward declaration
class GameCharacter;

class HealthCalcFunc {
public:
    virtual int calc(const GameCharacter& gc) const;
};

class HealthCalcFuncDerived : public HealthCalcFunc {
public:
    virtual int calc(const GameCharacter& gc) const override;
};

class GameCharacter {
public:
    // ctor
    GameCharacter(HealthCalcFunc* pFunc) : pHealthFunc(pFunc) {}
    // public interface
    int healthValue() const;
    // public setter for the function pointer
    void setHealthFunc(HealthCalcFunc* pFunc) {
        pHealthFunc = pFunc;
    }
private:
    HealthCalcFunc* pHealthFunc;
};



} // namespace additional_hierarchy