#ifndef C_PRIMER_5TH_HASPTR_H
#define C_PRIMER_5TH_HASPTR_H

#include <string>
#include <iostream>
#include <utility>

class HasPtr {
    friend void swap(HasPtr &left, HasPtr &right);

    friend bool operator<(const HasPtr &lhs, const HasPtr &rhs);

public:
    HasPtr() = default;

    explicit HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}

    HasPtr(const HasPtr &other) : ps(new std::string(*other.ps)), i(other.i) {}

    HasPtr(HasPtr &&other) noexcept : ps(other.ps), i(other.i) { other.ps = nullptr; }

    HasPtr &operator=(HasPtr other);

    HasPtr &operator=(HasPtr &&other) noexcept;

    ~HasPtr() { delete ps; }

private:
    std::string *ps = nullptr;
    int i = 0;
};

inline HasPtr &HasPtr::operator=(HasPtr other) {
    swap(other, *this);
    return *this;
}

inline HasPtr &HasPtr::operator=(HasPtr &&other) noexcept {
    if (this != &other) {
        delete ps;
        ps = other.ps;
        i = other.i;
        other.ps = nullptr;
    }
    return *this;
}

inline void swap(HasPtr &left, HasPtr &right) {
    using std::swap;
    swap(left.ps, right.ps);
    swap(left.i, right.i);
}

inline bool operator<(const HasPtr &lhs, const HasPtr &rhs) { return *lhs.ps < *rhs.ps; }

#endif //C_PRIMER_5TH_HASPTR_H
