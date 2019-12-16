#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Sales_data_8.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " [FILE]\n";
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Failed to open \'" << argv[1] << "\'\n";
        return EXIT_FAILURE;
    }

    Sales_data total;
    if (read(ifs, total)) {
        Sales_data trans;
        while (read(ifs, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(std::cout, total) << '\n';
                total = trans;
            }
        }
        print(std::cout, total) << '\n';
    } else {
        std::cerr << "No data?!" << '\n';
    }

    return 0;
}
