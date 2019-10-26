#include <iostream>
#include <string>

int main() {
    do {
        std::string s1, s2;
        std::cout << "Enter two lines" << std::endl;
        if (std::getline(std::cin, s1) && std::getline(std::cin, s2))
            std::cout << "The line " << (s1 > s2 ? s1 : s2) << " is larger." << std::endl;
    } while (std::cin);

    return 0;
}
