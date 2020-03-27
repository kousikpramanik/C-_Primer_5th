#ifndef C_PRIMER_5TH_HASPTR_H
#define C_PRIMER_5TH_HASPTR_H

#include <string>
#include <cstdlib>

class HasPtr {
public:
    explicit HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) {}

    HasPtr(const HasPtr &other) : ps(other.ps), i(other.i), use(other.use) { ++*use; }

    HasPtr &operator=(const HasPtr &other);

    ~HasPtr();

private:
    std::string *ps;
    int i;
    std::size_t *use;
};

inline HasPtr &HasPtr::operator=(const HasPtr &other) {
    if (this != &other) {
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        ps = other.ps;
        i = other.i;
        use = other.use;
        ++*use;
    }
    return *this;
}

inline HasPtr::~HasPtr() {
    if (--*use == 0) {
        delete ps;
        delete use;
    }
}

#endif //C_PRIMER_5TH_HASPTR_H
