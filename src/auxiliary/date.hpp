#pragma once

class Date {
public:
    Date(int y, int m, int d);
    Date(const Date& rhs) : y_(rhs.y_), m_(rhs.m_), d_(rhs.d_) {}
    Date& operator=(const Date& rhs) {
        y_ = rhs.y_;
        m_ = rhs.m_;
        d_ = rhs.d_;
        return *this;
    }
    ~Date() {}
    void print() const;
private:
    int y_, m_, d_;
};