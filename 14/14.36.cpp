#include "line_istream.h"

#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<std::string> svec;
    line_istream line_cin;
    while (std::cin) { svec.push_back(line_cin()); }
    for (const auto &s : svec) { std::cout << s << '\n'; }
    return 0;
}
