#ifndef PERSON_5_H_
#define PERSON_5_H_

#include <iostream>
#include <string>

class Person;

std::istream &read(std::istream &is, Person &obj);

std::ostream &print(std::ostream &os, const Person &obj);

class Person {
private:
    std::string name;
    std::string address;
public:
    Person(const std::string &inp_name) : name(inp_name) {}

    Person(const std::string &inp_name, const std::string &inp_addr) : name(inp_name), address(inp_addr) {}

    Person(std::istream &is) {
        read(is, *this);
    }

    const std::string &ret_name() const {
        return name;
    }

    const std::string &ret_address() const {
        return address;
    }

    friend std::istream &read(std::istream &is, Person &obj);

    friend std::ostream &print(std::ostream &os, const Person &obj);
};

#endif
