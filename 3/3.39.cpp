#include <iostream>
#include <string>
#include <cstdio>
#include <cstddef>
#include <cstring>

int main() {
    std::string s1, s2;
    std::cout << "Enter string 1: ";
    std::getline(std::cin, s1);
    std::cout << "Enter string 2: ";
    std::getline(std::cin, s2);
    if (s1 == s2)
        std::cout << "The strings are equal." << std::endl;
    else
        std::cout << "The strings are not equal." << std::endl;

    constexpr size_t str_size = 40;
    char a[str_size], b[str_size];
    std::cout << "Enter C style string 1: ";
    std::fgets(a, str_size, stdin);
    std::cout << "Enter C style string 2: ";
    std::fgets(b, str_size, stdin);
    if (std::strcmp(a, b) == 0)
        std::cout << "The C style strings are equal." << std::endl;
    else
        std::cout << "The C style strings are not equal." << std::endl;

    return 0;
}
