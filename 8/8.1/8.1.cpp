#include "8.1.h"

#include <iostream>

std::istream &printIstream(std::istream &is) {
    char ch;

    while (true) {
        is.get(ch); // unformatted input
        if (!is) // if input failed, ch would have remained same
            break;
        std::cout << ch;
    }
    is.clear();

    return is;
}
