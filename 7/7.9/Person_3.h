#ifndef PERSON_3_H_
#define PERSON_3_H_

#include <iostream>
#include <string>

struct Person {
    std::string name;
    std::string address;

    const std::string &ret_name() const {
        return name;
    }

    const std::string &ret_address() const {
        return address;
    }
};

std::istream &read(std::istream &is, Person &obj);

std::ostream &print(std::ostream &os, const Person &obj);

#endif
