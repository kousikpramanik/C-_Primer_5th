#include <iostream>
#include <stdexcept>
#include "Chapter6.h"

int main() {
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

    return 0;
}
