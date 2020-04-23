#include <map>
#include <string>
#include <functional>
#include <iostream>
#include <stdexcept>

int main() {
    const std::map<std::string, std::function<int(int, int)>> operations = {{"+", std::plus<int>()},
                                                                            {"-", std::minus<int>()},
                                                                            {"*", std::multiplies<int>()},
                                                                            {"/", std::divides<int>()},
                                                                            {"%", std::modulus<int>()}};
    int lhs, rhs;
    std::string op;
    std::cout << "This is a simple desk calculator.\n> ";
    while (std::cin >> lhs >> op >> rhs) {
        try {
            std::cout << operations.at(op)(lhs, rhs) << "\n> ";
        } catch (const std::out_of_range &err) {
            std::cout << "> ";
            continue;
        }
    }
    return 0;
}
