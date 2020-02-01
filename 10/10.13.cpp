#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

bool isLenAtleast5(const std::string &s) {
    return (s.length() >= 5);
}

int main() {
    std::vector<std::string> svec;
    for (std::string input; std::cin >> input;) { svec.push_back(input); }
    auto lenAtleast5 = std::partition(svec.begin(), svec.end(), isLenAtleast5);
    std::cout << "Words with length at least 5: ";
    for (decltype(svec.cbegin()) curr = svec.cbegin(), end = lenAtleast5; curr != end; ++curr) {
        std::cout << *curr << ' ';
    };
    std::cout << '\n';
    return 0;
}
