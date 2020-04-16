#ifndef C_PRIMER_5TH_PERSON_H
#define C_PRIMER_5TH_PERSON_H

#include <iostream>
#include <string>

struct Person;

std::istream &read(std::istream &is, Person &obj);

std::ostream &print(std::ostream &os, const Person &obj);

struct Person {
    Person(const std::string &inp_name) : name(inp_name) {}

    Person(const std::string &inp_name, const std::string &inp_addr) : name(inp_name), address(inp_addr) {}

    Person(std::istream &is) { read(is, *this); }

    std::string name;
    std::string address;

    const std::string &ret_name() const { return name; }

    const std::string &ret_address() const { return address; }
};

#endif // C_PRIMER_5TH_PERSON_H
