#ifndef PERSON_2_H_
#define PERSON_2_H_

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

#endif
