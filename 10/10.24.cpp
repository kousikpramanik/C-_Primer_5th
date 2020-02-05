#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

bool check_size(const std::string &s, std::string::size_type sz) { return s.length() >= sz; }

int main() {
    std::cout << "Enter a word: ";
    std::string uselen;
    std::cin >> uselen;

    std::cout << "Keep entering text: ";
    std::vector<std::string> svec;
    for (std::string input; std::cin >> input;) { svec.push_back(input); }

    auto match = std::find_if(svec.cbegin(), svec.cend(),
                              std::bind(check_size, std::placeholders::_1, uselen.length() + 1));
    if (match == svec.cend()) {
        std::cout << "No word of length greater than the length of \"" << uselen << "\" exists in the given input.\n";
    } else {
        std::cout << "\"" << *match
                  << "\" is the first word in the given input whose length is greater than the length of \"" << uselen
                  << "\".\n";
    }

    return 0;
}
