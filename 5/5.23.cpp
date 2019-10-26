#include <iostream>

int main() {
    int dividend, divisor;
    std::cout << "Enter two integers: ";
    if (std::cin >> dividend >> divisor) {
        std::cout << dividend << " / " << divisor << " = " << dividend / divisor << std::endl;
    }

    return 0;
}
