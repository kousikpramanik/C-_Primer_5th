#include <iostream>
#include <cstdlib>
#include <cstring>

int main() {
    std::size_t size;
    std::cout << "Enter how many characters you want to type: ";
    std::cin >> size;
    ++size; // account for null character
    if (size < 2) {
        std::cerr << "Invalid size.\n";
        return EXIT_FAILURE;
    }
    for (int ch; (ch = std::getchar()) != '\n' && ch != EOF;) {}

    std::cout << "Enter the string.\n";
    auto string = new char[size];
    if (string != std::fgets(string, size, stdin)) {
        std::cerr << "Failed to read data.\n";
        return EXIT_FAILURE;
    }
    {
        auto newline = std::strchr(string, '\n');
        if (newline) { *newline = '\0'; }
    }

    std::cout << string << '\n';

    delete[] string;
    return EXIT_SUCCESS;
}
