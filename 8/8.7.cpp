#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include "Sales_data.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " [INPUT FILE] [OUTPUT FILE] append(optional)\n";
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "Failed to open \'" << argv[1] << "\'\n";
        return EXIT_FAILURE;
    }

    std::ofstream ofs;
    if (argc == 4 && (std::strcmp(argv[3], "append") == 0))
        ofs.open(argv[2], std::fstream::out | std::fstream::app);
    else
        ofs.open(argv[2]); // out and trunc

    if (!ofs) {
        std::cerr << "Failed to open \'" << argv[2] << "\'\n";
        return EXIT_FAILURE;
    }

    Sales_data total;
    if (read(ifs, total)) {
        Sales_data trans;
        while (read(ifs, trans)) {
            if (total.isbn() == trans.isbn())
                total.combine(trans);
            else {
                print(ofs, total) << '\n';
                total = trans;
            }
        }
        print(ofs, total) << '\n';
    } else {
        std::cerr << "No data?!" << '\n';
    }

    return 0;
}
