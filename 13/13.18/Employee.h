#ifndef C_PRIMER_5TH_EMPLOYEE_H
#define C_PRIMER_5TH_EMPLOYEE_H

#include <string>
#include <cstdlib>

class Employee {
public: // constructors
    Employee() : eID(next_valid++) {}

    explicit Employee(const std::string &s) : name(s), eID(next_valid++) {}

    Employee(const Employee &other) : name(other.name), eID(next_valid++) {}

    Employee &operator=(const Employee &other) {
        if (this != &other) {
            name = other.name;
            eID = next_valid++;
        }
        return *this;
    }

public: // public data
    std::string name;
private: // private data
    std::size_t eID;
private: // class data
    static std::size_t next_valid;
};

#endif // C_PRIMER_5TH_EMPLOYEE_H
