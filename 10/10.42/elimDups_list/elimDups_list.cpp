#include "elimDups_list.h"

#include <list>
#include <string>
#include <iostream>

void elimDups_list(std::list<std::string> &slst) {
#ifndef NDEBUG
    std::clog << "In file: " << __FILE__ << "\nIn function: " << __func__ << "\n";
    std::clog << "Before duplicate elimination: ";
    for (const auto &s : slst) { std::clog << s << ' '; }
    std::clog << '\n';
#endif // NDEBUG

    slst.sort();
#ifndef NDEBUG
    std::clog << "After call to sort(): ";
    for (const auto &s : slst) { std::clog << s << ' '; }
    std::clog << '\n';
#endif // NDEBUG

    slst.unique();
#ifndef NDEBUG
    std::clog << "After duplicate elimination: ";
    for (const auto &s : slst) { std::clog << s << ' '; }
    std::clog << '\n';
#endif // NDEBUG
}
