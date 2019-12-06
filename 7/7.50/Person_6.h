#ifndef PERSON_6_H_
#define PERSON_6_H_

#include <iostream>
#include <string>

class Person {
    friend std::istream &read(std::istream &is, Person &obj);

    friend std::ostream &print(std::ostream &os, const Person &obj);

public:
    explicit Person(const std::string &inp_name) : name(inp_name) {}

    Person(const std::string &inp_name, const std::string &inp_addr) : name(inp_name), address(inp_addr) {}

    Person(std::istream &is) { read(is, *this); }

public:
    const std::string &ret_name() const { return name; }

    const std::string &ret_address() const { return address; }

private:
    std::string name;
    std::string address;
};

std::istream &read(std::istream &is, Person &obj);

std::ostream &print(std::ostream &os, const Person &obj);

#endif
