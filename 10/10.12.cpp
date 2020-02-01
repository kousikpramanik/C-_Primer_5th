#include <iostream>
#include <vector>
#include "Sales_data_8.h"
#include <algorithm>

bool compareISBN(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() < rhs.isbn();
}

int main() {
    std::vector<Sales_data> sdvec;
    for (Sales_data input; read(std::cin, input);) { sdvec.push_back(input); }
    std::cout << "Before sorting:\n";
    for (const auto &sd : sdvec) { print(std::cout, sd) << '\n'; }

    std::sort(sdvec.begin(), sdvec.end(), compareISBN);
    std::cout << "After sorting:\n";
    for (const auto &sd : sdvec) { print(std::cout, sd) << '\n'; }

    return 0;
}
