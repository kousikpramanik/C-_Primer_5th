#ifndef C_PRIMER_5TH_HASPTR_H
#define C_PRIMER_5TH_HASPTR_H

#include <string>
#include <iostream>
#include <utility>

class HasPtr {
    friend void swap(HasPtr &left, HasPtr &right);

    friend bool operator<(const HasPtr &lhs, const HasPtr &rhs);

public:
    explicit HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr &other) : ps(new std::string(*other.ps)), i(other.i) {}

    HasPtr &operator=(HasPtr other);

    ~HasPtr() { delete ps; }

private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &left, HasPtr &right) {
    using std::swap;
#ifndef NDEBUG
    std::clog << "In file: " << __FILE__ << "\nIn function: " << __func__ << "\n";
    std::clog << "*left.ps: \"" << *left.ps << "\", *right.ps: \"" << *right.ps << "\"\n";
#endif //NDEBUG
    swap(left.ps, right.ps);
    swap(left.i, right.i);
}

inline bool operator<(const HasPtr &lhs, const HasPtr &rhs) { return *lhs.ps < *rhs.ps; }

#endif //C_PRIMER_5TH_HASPTR_H
