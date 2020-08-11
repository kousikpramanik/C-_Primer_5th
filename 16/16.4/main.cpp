#include <vector>
#include <list>
#include <string>
#include "find.h"
#include <iostream>

int main() {
    std::vector<int> ivec{1, 2, 3, 4, 5};
    std::list<std::string> slst{"1", "2", "3", "4", "5"};
    if (::find(ivec.cbegin(), ivec.cend(), 2) != ivec.cend()) {
        std::cout << "Test 1: succeeded\n";
    }
    if (::find(ivec.cbegin(), ivec.cend(), 99) == ivec.cend()) {
        std::cout << "Test 2: succeeded\n";
    }
    if (::find(slst.cbegin(), slst.cend(), "2") != slst.cend()) {
        std::cout << "Test 3: succeeded\n";
    }
    if (::find(slst.cbegin(), slst.cend(), "99") == slst.cend()) {
        std::cout << "Test 4: succeeded\n";
    }

    return 0;
}
