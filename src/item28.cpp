#include <iostream>

class Point {
public:
    Point(int x, int y): x_(x), y_(y) {}
    int x() const { return x_; }
    int y() const { return y_; }
private:
    int x_, y_;
};

/* Avoid returning handles (references, pointers, iterators) to object's internal data 
   which can change the encapsulation of the class 
*/

class Rectangle {
public:
    Rectangle(Point topLeft, Point bottomRight): topLeft_(topLeft), bottomRight_(bottomRight) {}
    // const is necessary, otherwise it will be public to change 
    const Point& topLeft() const { return topLeft_; }
    const Point& bottomRight() const { return bottomRight_; }
private:
    Point topLeft_, bottomRight_;
};

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        Point p1(1, 2);
        Point p2(3, 4);
        Rectangle r(p1, p2);
        std::cout << "topLeft: " << r.topLeft().x() << ", " << r.topLeft().y() << std::endl;
        std::cout << "bottomRight: " << r.bottomRight().x() << ", " << r.bottomRight().y() << std::endl;

        // easy to change the original object. If const Point& is changed to const Point then it won't change the original object
        const Point& tl = r.topLeft();
        const_cast<Point&>(tl) = Point(5, 6); 
        std::cout << "topLeft: " << r.topLeft().x() << ", " << r.topLeft().y() << std::endl;
        std::cout << "bottomRight: " << r.bottomRight().x() << ", " << r.bottomRight().y() << std::endl;

        // dangling pointer if r is destroyed
        const Point* p = &(r.topLeft());
        const_cast<Point&>(*p) = Point(7, 8);
        std::cout << "topLeft: " << r.topLeft().x() << ", " << r.topLeft().y() << std::endl;
        std::cout << "bottomRight: " << r.bottomRight().x() << ", " << r.bottomRight().y() << std::endl;
    }
    return 0;
}