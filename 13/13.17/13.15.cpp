#include <cstdlib>
#include <iostream>

class numbered {
public: // constructors
    numbered() : mysn(curr++) {}

    numbered(const numbered &other) : mysn(curr++) {}

    numbered &operator=(const numbered &other) {
        if (this != &other) { mysn = curr++; }
        return *this;
    }

public: // data
    std::size_t mysn = 0;

private: // unique serial number
    static std::size_t curr;
};

std::size_t numbered::curr = 0;

inline void f(numbered s) { std::cout << s.mysn << '\n'; }

int main() {
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);

    return 0;
}
