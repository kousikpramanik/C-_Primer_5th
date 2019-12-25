#include <iostream>
#include <string>
#include <list>

int main() {
    std::list<std::string> lststr;

    std::string input;
    while (std::cin >> input) { lststr.push_back(input); }

    for (std::list<std::string>::const_iterator curr = lststr.cbegin(), end = lststr.cend(); curr != end; ++curr) {
        std::cout << *curr << ' ';
    }
    std::cout << '\n';

    return 0;
}
