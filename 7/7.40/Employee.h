#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <string>
#include <vector>

class Employee {
    friend std::istream &read(std::istream &is, Employee empl);

public:
    Employee(std::string n, std::string e, std::string d, std::string p, double s) : name(n), empID(e), deptID(d),
                                                                                     position(p), salary(s) {}

    Employee(std::istream &is) { read(is, *this); }

private:
    std::string name;
    std::string empID;
    std::string deptID;
    std::string position;
    double salary = 0.0;
    std::vector<std::string> notes;
};

std::istream &read(std::istream &is, Employee empl);

#endif
