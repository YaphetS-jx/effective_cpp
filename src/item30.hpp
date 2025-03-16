#pragma once

// template functions can be expanded inlined at the point of call site
template<typename T>
inline const T& max(const T& a, const T&b) {
    return a < b ? b : a;
}

class Widget {
    int x, y;
public:
    // member functions are inline by default if defined in header file
    // Don't inline ctor and dtor, which are much larger than it appears. 
    Widget() {};
    ~Widget() {};
};