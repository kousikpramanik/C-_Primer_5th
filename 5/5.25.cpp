#include <iostream>
#include <stdexcept>

int main() {
    int dividend, divisor;
    std::cout << "Enter two integers: ";
    while (std::cin >> dividend >> divisor) {
        try {
            if (divisor == 0)
                throw std::domain_error("Divisor cannot be zero.");
            std::cout << dividend << " / " << divisor << " = " << dividend / divisor << std::endl;
            break;
        } catch (std::domain_error &err) {
            std::cout << err.what() << "\nWant to try again? (enter y or n): ";
            char c;
            std::cin >> c;
            if (!std::cin || c != 'y')
                break;
        }
    }

    return 0;
}
