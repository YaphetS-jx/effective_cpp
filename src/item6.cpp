
class A {
public:
    // constructor
    A(int i) : val(i) {};

    // delete copy constructor
    A(const A & rhs) = delete;

    // delete copy assignment operator 
    A & operator= (const A& rhs) = delete;

    // desctructor
    ~A() {};

private:
    int val;
    // older way, declare copy operator and copy assignment operator as private
    // A(const A & rhs);
    // A & operator= (const A& rhs);

};


// create a base class that has deleted copy constructor and copy assignment operator
class Uncopyable {
public:
    Uncopyable() {};
    ~Uncopyable() {};

    // delete copy constructor and copy assignment operator
    Uncopyable(const Uncopyable & rhs) = delete;
    Uncopyable & operator= (const Uncopyable & rhs) = delete;
};

// private inheritance will make the copy constructor and copy assignment operator of Uncopyable private
// private inheritance makes all interface of Uncopyable private
class B: private Uncopyable {
public:
    int val;
    B(int i) : val(i) {};
};


int main () {
    A a(1);

    // this will fail because copy constructor is deleted
    // A b = a;
    // A b(a);

    B bb(1);
    // both are wrong 
    // B bba(bb);
    // B bba = bb;

    return 0;
}