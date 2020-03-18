#include <iostream>
#include <vector>

struct X {
    X() { std::cout << "X()\n"; }

    X(const X &other) { std::cout << "X(const X&)\n"; }

    X &operator=(const X &other) {
        std::cout << "X &operator=(const X&)\n";
        return *this;
    }

    ~X() { std::cout << "~X()\n"; }
};

inline void nonref(X x) {}

inline void ref(X &x) {}

inline X fn() { return X(); }

int main() {
    std::cout << "Creating on stack.\n";
    X x;

    std::cout << "\nPassing as nonreference.\n";
    nonref(x);

    std::cout << "\nPassing as reference.\n";
    ref(x);

    std::cout << "\nCreating in free store.\n";
    auto px = new X;

    std::cout << "\nDeleting from free store.\n";
    delete px;
    px = nullptr;

    std::cout << "\nGetting from function and direct-initialising.\n";
    X fx = fn();

    std::cout << "\nIn container.\n";
    std::vector<X> test;

    std::cout << "\nPush to container.\n";
    test.push_back(x);
    test.push_back(fx);
    test.emplace_back();

    std::cout << "\nEmpty container.\n";
    test.clear();
    test.shrink_to_fit();

    std::cout << "\nReserve container first, then push.\n";
    test.reserve(3);
    test.push_back(x);
    test.push_back(fx);
    test.emplace_back();

    std::cout << "\nPush an extra element than reserved size.\n";
    test.push_back(x);

    std::cout << "\nDuring return.\n";
    return 0;
}
