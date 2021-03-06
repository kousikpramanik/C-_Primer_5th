#include <iostream>
#include <cstdlib>
#include <fstream>
#include "Query.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [FILE NAME]\n";
        return EXIT_FAILURE;
    }
    std::ifstream inp(argv[1]);
    if (!inp) {
        std::cerr << "Error opening file: \"" << argv[1] << "\"\n";
        return EXIT_FAILURE;
    }
    Query q = Query("fiery") & Query("bird") | Query("wind");
    print(std::cout, q.eval(inp));
    return EXIT_SUCCESS;
}
