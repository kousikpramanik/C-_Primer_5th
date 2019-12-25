#include <iostream>
#include <string>
#include <deque>

int main() {
    std::deque<std::string> dqstr;

    std::string input;
    while (std::cin >> input) { dqstr.push_back(input); }

    for (std::deque<std::string>::const_iterator curr = dqstr.cbegin(), end = dqstr.cend(); curr != end; ++curr) {
        std::cout << *curr << ' ';
    }
    std::cout << '\n';

    return 0;
}
