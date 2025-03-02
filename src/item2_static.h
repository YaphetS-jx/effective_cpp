class A {
public:
    int data;
    explicit A(int x) : data(x) {};
    ~A() {};

    // both decalre and define in class
    static const int x = 1;

    // only declare in class
    static const int y;
};