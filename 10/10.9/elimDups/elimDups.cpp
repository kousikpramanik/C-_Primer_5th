#include "elimDups.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

void elimDups(std::vector<std::string> &svec) {
#ifndef NDEBUG
    std::clog << "In file: " << __FILE__ << "\nIn function: " << __func__ << "\n";
    std::clog << "Before duplicate elimination: ";
    for (const auto &s : svec) { std::clog << s << ' '; }
    std::clog << '\n';
#endif //NDEBUG

    std::sort(svec.begin(), svec.end());
#ifndef NDEBUG
    std::clog << "After call to std::sort(): ";
    for (const auto &s : svec) { std::clog << s << ' '; }
    std::clog << '\n';
#endif //NDEBUG

    auto erase_from = std::unique(svec.begin(), svec.end());
#ifndef NDEBUG
    std::clog << "The following output has unspecified values, starting from the iterator returned by the call\n";
    std::clog << "After call to std::unique(): ";
    for (const auto &s : svec) { std::clog << s << ' '; }
    std::clog << '\n';
#endif //NDEBUG

    svec.erase(erase_from, svec.end());
#ifndef NDEBUG
    std::clog << "After duplicate elimination: ";
    for (const auto &s : svec) { std::clog << s << ' '; }
    std::clog << '\n';
#endif //NDEBUG
}
