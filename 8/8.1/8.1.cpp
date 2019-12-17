#include "8.1.h"

#include <iostream>

std::istream &printIstream(std::istream &is) {
    char ch;
    while (is.get(ch)) { std::cout << ch; } // unformatted input

    is.clear();
    return is;
}
