#include <fstream>
#include "TextQuery.h"
#include <iostream>
#include <string>
#include <cstdlib>

void runQueries(std::ifstream &infile) {
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") { break; }
        std::cout << tq.query(s) << '\n';
    }
    // DebugDelete() will be called a bunch of times when this scope ends
}

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
    runQueries(inp);
    return EXIT_SUCCESS;
    // DebugDelete() on the static empty set will be called when this scope ends
}
