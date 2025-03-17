#pragma once

namespace nvi {
    
class GameCharacter {
public:
    int healthValue() const; // public interface
private:
    virtual int doHealthValue() const; // private implementation
};

class EvilBadGuy : public GameCharacter {
private:
    virtual int doHealthValue() const override; // private implementation in derived class
};

} // namespace nvi