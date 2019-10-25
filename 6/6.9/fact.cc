#include "Chapter6.h"
#include <stdexcept>

unsigned fact(unsigned n) {
    unsigned ret = 1;
    while (n > 1) {
        unsigned prev = ret;
        ret *= n;
        if (ret / n != prev)
            throw std::overflow_error("Overflow!");
        --n;
    }

    return ret;
}
