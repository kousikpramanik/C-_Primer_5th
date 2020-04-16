#ifndef C_PRIMER_5TH_PERSON_H
#define C_PRIMER_5TH_PERSON_H

#include <iostream>
#include <string>

struct Person {
    std::string name;
    std::string address;

    const std::string &ret_name() const { return name; }

    const std::string &ret_address() const { return address; }
};

std::istream &read(std::istream &is, Person &obj);

std::ostream &print(std::ostream &os, const Person &obj);

#endif // C_PRIMER_5TH_PERSON_H
