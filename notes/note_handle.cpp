#include <iostream>
#include <memory>    // For std::unique_ptr


struct Data;
typedef Data * handle;
void handleInit(handle *p, int x);
void freeHandle(handle p);


struct Data {
    int x;
    Data(int x) : x(x) { std::cout << "Data::Data(" << x << ")\n"; }
    ~Data() {std::cout << "Data::~Data(" << x << ")\n"; }
};

typedef Data * handle;

struct Deleter {
    int y;
    Deleter(int y) : y(y) { std::cout << "Deleter::ctor(y * " << y << ")\n"; }
public:
    void operator()(handle p) {
        std::cout << "Deleter::operator()(Data * " << p->x << "), " << "inside y " << y << std::endl;
       
        // delete p;
        freeHandle(p);
    }
    void setY(int y) { this->y = y; }
};


void handleInit(handle *p, int x) {
    *p = new Data(x);
}

void freeHandle(handle p) {
    std::cout << "freeHandle(" << p->x << ")\n";
    delete p;
}

int main() {    
    std::cout << "-------------------------------------------" << std::endl;
    {
        handle p = nullptr;
        handleInit(&p, 2);
        std::cout << "p->x = " << p->x << "\n";
        freeHandle(p);
    }

    std::cout << "-------------------------------------------" << std::endl;
    {
        handle p = nullptr;
        handleInit(&p, 1);
        auto p1 = std::unique_ptr<Data, Deleter>(p, Deleter(3));
        std::cout << "typeid(p1).name() = " << typeid(p1).name() << "\n";        

        p1.get_deleter().setY(4);

        auto p2 = std::move(p1);
        std::cout << "typeid(p2).name() = " << typeid(p2).name() << "\n";
    }

    return 0;
}