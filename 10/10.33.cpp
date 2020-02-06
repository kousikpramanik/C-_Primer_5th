#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iterator>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " [INPUT] [OUTPUT_ODD] [OUTPUT_EVEN]\n";
        return EXIT_FAILURE;
    }

    std::ifstream inp(argv[1]);
    std::ofstream out_odd(argv[2]);
    std::ofstream out_even(argv[3]);
    if (!inp || !out_odd || !out_even) {
        std::cerr << "Error opening files.\n";
        return EXIT_FAILURE;
    }
    std::istream_iterator<int> inp_iter(inp), eof;
    std::ostream_iterator<int> out_odd_iter(out_odd, " "), out_even_iter(out_even, "\n");
    while (inp_iter != eof) {
        if (*inp_iter % 2) {
            out_odd_iter = *inp_iter++;
        } else {
            out_even_iter = *inp_iter++;
        }
    }

    return EXIT_SUCCESS;
}
