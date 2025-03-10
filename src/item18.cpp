#include <iostream>
#include <memory> 

/* Design the code easy to use correctly and hard ot use incorrectly */
// 1st way: add constraints to the values and create explicit constructors
// 2nd way: predefine all valid values
struct Day {
    explicit Day(int d) : val(d) {
        if (d < 1 || d > 31) throw std::out_of_range("Day out of range");
    };
    int val;
};
struct Month {
    explicit Month(int m) : val(m) {
        if (m < 1 || m > 12) throw std::out_of_range("Month out of range");
    };
    int val;
    // 2nd way 
    static Month Jan() { return Month(1); }
    static Month Feb() { return Month(2); }
    // similar for other months
};
struct Year {
    explicit Year(int y) : val(y) {
        if (y < 1900) throw std::out_of_range("Year out of range");
    };
    int val;
};

class Date {
public: 
    Date(const Day& d, const Month& m, const Year& y) : day(d), month(m), year(y) {};
    void print() {
        std::cout << "Date: " << day.val << "/" << month.val << "/" << year.val << std::endl;
    };
    ~Date() {
        std::cout << "Date destroyed" << std::endl;
    }
private:
    Day day;
    Month month;
    Year year;
};

// return a smart pointer in the factory function to avoid risk of memory leak
std::unique_ptr<Date> getDate(const Day &d, const Month &m, const Year &y) {
    return std::make_unique<Date>(d, m, y);
}

// provide a functor as deleter for the smart pointer 
class Deleter {
public:
    void operator()(Date *p) {
        std::cout << "customized deleter" << std::endl;
        delete p;
    }
};

std::unique_ptr<Date, Deleter> getDate2(const Day &d, const Month &m, const Year &y) {
    return std::unique_ptr<Date, Deleter>(new Date(d, m, y));
}

int main() {
    std::cout << "----------------- test -----------------" << std::endl;

    {
        Date date(Day(1), Month::Jan(), Year(2025));
        date.print();
        try {
            Day d(32);
        } catch (const std::out_of_range &e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
    }
    
    std::cout << "----------------- test -----------------" << std::endl;
    {
        auto date = getDate(Day(1), Month::Jan(), Year(2025));
        date->print();

        auto date2 = getDate2(Day(1), Month::Jan(), Year(2025));
        date2->print();
    }

    return 0;
}