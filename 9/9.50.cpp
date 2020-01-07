#include <vector>
#include <string>
#include <iostream>

int isum_svec(const std::vector<std::string> svec) {
    int ret(0);
    for (const auto &s : svec) { ret += std::stoi(s); }

    return ret;
}

double dsum_svec(const std::vector<std::string> svec) {
    double ret(0);
    for (const auto &s : svec) { ret += std::stod(s); }

    return ret;
}

int main() {
    std::vector<std::string> svec{"0", "1", "1", "2", "3", "5", "8", "13", "21", "34", "55", "89"};
    std::cout << isum_svec(svec) << '\n';
    std::cout << dsum_svec(svec) << '\n';

    return 0;
}
