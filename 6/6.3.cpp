#include <iostream>

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

int main() {
    std::cout << "0! = " << fact(0) << std::endl;
    std::cout << "1! = " << fact(1) << std::endl;
    int a = 9;
    std::cout << a << "! = " << fact(a) << std::endl;

    return 0;
}
