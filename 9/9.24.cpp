#include <vector>
#include <stdexcept>
#include <iostream>

int main() {
    std::vector<int> vec;

    try {
        std::cout << vec.at(0) << '\n';
    } catch (const std::out_of_range &err) {
        std::cerr << err.what() << '\n';
    }

    // std::cout << vec[0] << '\n'; // undefined behaviour
    // std::cout << vec.front() << '\n'; // same
    // std::cout << *vec.cbegin() << '\n'; // same

    return 0;
}
