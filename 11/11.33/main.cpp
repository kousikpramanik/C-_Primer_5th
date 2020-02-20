#include <fstream>
#include <iostream>
#include <cstdlib>
#include <exception>
#include "word_transform.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <transformation rule file> <input file>\n";
        return EXIT_FAILURE;
    }
    std::ifstream map_file(argv[1]);
    if (!map_file) {
        std::cerr << "Failed to open \'" << argv[1] << "\'\n";
        return EXIT_FAILURE;
    }
    std::ifstream input(argv[2]);
    if (!input) {
        std::cerr << "Failed to open \'" << argv[2] << "\'\n";
        return EXIT_FAILURE;
    }
    try {
        word_transform(map_file, input);
    } catch (const std::runtime_error &err) {
        std::cerr << err.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
