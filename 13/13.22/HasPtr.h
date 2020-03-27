#ifndef C_PRIMER_5TH_HASPTR_H
#define C_PRIMER_5TH_HASPTR_H

#include <string>

class HasPtr {
public:
    explicit HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr &other) : ps(new std::string(*other.ps)), i(other.i) {}

    HasPtr &operator=(const HasPtr &other) {
        if (this != &other) {
            // copying the string contents
            *ps = *other.ps;
            i = other.i;
        }
        return *this;
    }

    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
};

#endif //C_PRIMER_5TH_HASPTR_H
