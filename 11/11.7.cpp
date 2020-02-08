#include <map>
#include <string>
#include <vector>
#include <iostream>

int main() {
    std::map<std::string, std::vector<std::string>> families;
    for (std::string input1, input2; true;) {
        std::cout << "Enter last name of child: ";
        if (!std::getline(std::cin, input1)) {
            break;
        }
        std::cout << "Enter first name of child: ";
        if (!std::getline(std::cin, input2)) {
            break;
        }
        families[input1].push_back(input2);
    }
    for (const auto &family : families) {
        std::cout << family.first << '\n';
        for (const auto &children : family.second) { std::cout << "\t" << children << '\n'; }
    }

    return 0;
}
