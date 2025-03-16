#include <iostream>
#include <memory>

/* Public inheritance means "is-a" relationship
   if Square is a Rectangle, then it should inherit from Rectangle
*/

class Rectangle {
public:
    Rectangle(int width, int height) : width_(width), height_(height) {}
    int width() const {return width_;}
    int height() const {return height_;}
    void makeBigger(int delta_width, int delta_height) {
        width_ += delta_width;
        height_ += delta_height;
    }
    virtual void print() const {
        std::cout << "Rectangle: " << width_ << ", " << height_ << std::endl;
    }
protected: 
    int width_;
    int height_;
};

/* makeBigger is inherited from Rectangle but conceptually it doesn't work for Square
   if the delta_width != delta_height, the square will become a rectangle */

class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {}
    void print() const override {
        std::cout << "Square: " << width_ << ", " << height_ << std::endl;
    }
};


int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        auto r = std::make_unique<Rectangle>(10, 20);
        r->print();
        r->makeBigger(10, 20);
        r->print();

        auto s = std::make_unique<Square>(10);
        s->print();
        s->makeBigger(10, 20);
        // now it doesn't make sense to be a square
        s->print();
    }
    return 0;
}