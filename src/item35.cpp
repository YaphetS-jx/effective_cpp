#include <iostream>
#include <memory>

/* Four alternatives to virtual functions:
 * 1. non-virtual interface (NVI) idiom
 * 2. function pointer data members 
 * 3. std::function data members
 * 4. virtual functions in a separate base class
 */


// example 1: NVI idiom
// Interface defined in base class along with default implementation of private functions
// Derived classes can override the private implementation while keeping the public interface
#include "auxiliary/nvi.hpp"

// example 2: function pointer data members
// use function pointer to store the address of the function
// easy to change the behavior of the object at runtime
#include "auxiliary/function_ptr.hpp"

// example 3: std::function data members
// use std::function to store the function pointer
// easy to change the behavior of the object at runtime
#include "auxiliary/std_function.hpp"

// example 4: virtual functions in a separate base class
// use virtual functions in another hierarchy to do the calculation
// easy to change the behavior of the object at runtime
#include "auxiliary/additional_hierarchy.hpp"

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace nvi;
        auto gc = std::make_unique<GameCharacter>();
        auto ebg = std::make_unique<EvilBadGuy>();
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
        std::cout << "ebg health value: " << ebg->healthValue() << std::endl;
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace function_ptr;
        auto gc = std::make_unique<GameCharacter>();
        // assign different function pointer to the object
        auto ebg = std::make_unique<EvilBadGuy>(additionalHealthCalc);
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
        std::cout << "ebg health value: " << ebg->healthValue() << std::endl;
        // change the behavior of the object at runtime
        gc->setHealthCalc(additionalHealthCalc);
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
    }
    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace std_function;
        auto gc = std::make_unique<GameCharacter>();
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
        // switch to functor
        // here has to be GameCharacterHealthFunc() not GameCharacterHealthFunc
        gc->setHealthCalc(GameCharacterHealthFunc());
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
        // switch to compatible function
        gc->setHealthCalc(calcHealthShort);
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
        // switch to member function
        auto gl = std::make_unique<GameLevel>();
        // we want to call healthCalcFunc(const GameCharacter& gc)
        // while float GameLevel::health(const GameCharacter& gc) actually expands to 
        // float GameLevel::health(this, const GameCharacter& gc) const
        // `this` is a pointer to GameLevel object
        // so we need a instance of GameLevel and assign the reference of GameCharacter to the second argument
        // which is done by std::placeholders::_1
        gc->setHealthCalc(std::bind(&GameLevel::health, gl.get(), std::placeholders::_1));
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
    }

    std::cout << "----------------- test -----------------" << std::endl;
    {
        using namespace additional_hierarchy;
        auto hc = std::make_unique<HealthCalcFunc>();        
        auto gc = std::make_unique<GameCharacter>(hc.get());
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
        auto hcd = std::make_unique<HealthCalcFuncDerived>();
        gc->setHealthFunc(hcd.get());
        std::cout << "gc health value: " << gc->healthValue() << std::endl;
    }
    return 0;
}