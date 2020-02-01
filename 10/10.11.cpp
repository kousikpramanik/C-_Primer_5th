#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "elimDups.h"

bool isShorter(const std::string &s1, const std::string &s2) {
    return s1.size() < s2.size();
}

int main() {
    std::vector<std::string> svec;
    for (std::string s; std::cin >> s;) { svec.push_back(s); }
    elimDups(svec);

    std::stable_sort(svec.begin(), svec.end(), isShorter);
    std::cout << "After call to std::stable_sort(): ";
    for (const auto &s : svec) { std::cout << s << ' '; }
    std::cout << '\n';

    return 0;
}
