#include <map>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <exception>
#include "Date.h"

int main() {
    std::map<std::string, std::vector<std::pair<std::string, Date>>> families;
    for (std::string last, first, dob; true;) {
        std::cout << "Enter last name of child: ";
        if (!getline(std::cin, last)) {
            break;
        }
        std::cout << "Enter first name of child: ";
        if (!getline(std::cin, first)) {
            break;
        }
        std::cout << "Enter the date of birth of the child: ";
        if (!getline(std::cin, dob)) {
            break;
        }
        families[last].emplace_back(first, dob);
    }
    for (const auto &family : families) {
        std::cout << family.first << '\n';
        for (const auto &children : family.second) {
            std::cout << "\t" << children.first << "\t\t";
            print(std::cout, children.second) << '\n';
        }
    }

    return 0;
}
