#include <iostream>
#include <stdexcept>

int main() {
    int dividend, divisor;
    std::cout << "Enter two integers: ";
    if (std::cin >> dividend >> divisor) {
        if (divisor == 0)
            throw std::domain_error("Divisor cannot be zero.");
        std::cout << dividend << " / " << divisor << " = " << dividend / divisor << std::endl;
    }

    return 0;
}
