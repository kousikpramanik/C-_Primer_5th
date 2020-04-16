#include <iostream>
#include "Sales_data.h"

int main() {
    Sales_data total(std::cin);
    if (std::cin) {
        Sales_data trans;
        while (read(std::cin, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(std::cout, total) << '\n';
                total = trans;
            }
        }
        print(std::cout, total) << '\n';
    } else
        std::cerr << "No data?!\n";

    return 0;
}
