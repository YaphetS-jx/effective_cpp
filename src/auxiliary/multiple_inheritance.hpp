#pragma once
#include <string>

/* one example where multiple inheritance is useful */

namespace multiple_inheritance {

// this is the public interface 
class IPerson {
public:
    virtual ~IPerson() = default;
    virtual std::string name() const = 0;
    virtual std::string email() const = 0;
};
class DatabaseID {};

// this is the private implementation
class PersonInfo {
public:
    explicit PersonInfo(DatabaseID pid) {};
    virtual ~PersonInfo() = default;
    virtual const char* theName() const {
        return "name";
    };
    virtual const char* theEmail() const {
        return "email";
    };
    virtual const char* valueDelimOpen() const {
        return "[";
    };
    virtual const char* valueDelimClose() const {
        return "]";
    };
};

// public interface + private implementation
class Person: public IPerson, private PersonInfo {
public:
    Person(DatabaseID pid): PersonInfo(pid) {}
    std::string name() const override {
        return valueDelimOpen() + std::string(PersonInfo::theName()) + valueDelimClose();
    }
    std::string email() const override {
        return valueDelimOpen() + std::string(PersonInfo::theEmail()) + valueDelimClose();
    }
private: 
    // override the default implementation, can only be done by inheritance
    const char *valueDelimOpen() const override {
        return "{";
    }
    const char *valueDelimClose() const override {
        return "}";
    }
};


} // namespace multiple_inheritance