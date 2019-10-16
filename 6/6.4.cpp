#include <iostream>
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

void askFact() {
    std::cout << "Enter an integer to calculate factorial: ";
    unsigned n;
    while (std::cin >> n) {
        try {
            std::cout << n << "! = " << fact(n) << std::endl;
            break;
        } catch (std::overflow_error &err) {
            std::cout << err.what() << "\nWant to try again? (Enter y or n): ";
            char c;
            if (!(std::cin >> c) || c != 'y')
                break;
        }
    }
}

int main() {
    askFact();

    return 0;
}
