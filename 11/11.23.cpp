#include <map>
#include <string>
#include <iostream>

int main() {
    std::multimap<std::string, std::string> families;
    for (std::string input1, input2; true;) {
        std::cout << "Enter last name of child: ";
        if (!std::getline(std::cin, input1)) {
            break;
        }
        std::cout << "Enter first name of child: ";
        if (!std::getline(std::cin, input2)) {
            break;
        }
        families.emplace(input1, input2);
    }
    for (auto curr = families.cbegin(), last = families.cend(); curr != last;) {
        std::cout << curr->first << '\n';
        auto range = families.equal_range(curr->first);
        while (range.first != range.second) {
            std::cout << '\t' << range.first->second << '\n';
            ++range.first;
        }
        curr = range.second;
    }

    return 0;
}
