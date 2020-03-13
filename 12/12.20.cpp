#include <iostream>
#include <cstdlib>
#include <fstream>
#include "StrBlob.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " [INPUT FILE]\n";
        return EXIT_FAILURE;
    }
    std::ifstream data_file(argv[1]);
    if (!data_file) {
        std::cerr << "Failed to open \'" << argv[1] << "\'\n";
        return EXIT_FAILURE;
    }

    StrBlob str_store;
    for (std::string input; std::getline(data_file, input);) { str_store.push_back(input); }

    for (auto iter = str_store.begin(), end = str_store.end(); unequal(iter, end); iter.incr()) {
        std::cout << iter.deref() << '\n';
    }

    return 0;
}
