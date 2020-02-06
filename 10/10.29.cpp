#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <vector>

int main() {
    std::string filename;
    std::cout << "Enter the filename: ";
    if (!(std::cin >> filename)) {
        std::cerr << "Error in filename input.\n";
        return EXIT_FAILURE;
    }
    std::ifstream inpfile(filename.c_str());
    if (!inpfile) {
        std::cerr << "Failed to open file \"" << filename << "\".\n";
        return EXIT_FAILURE;
    }
    std::istream_iterator<std::string> inpfile_iter(inpfile), eof;

    std::vector<std::string> svec(inpfile_iter, eof);
    for (const auto &s : svec) { std::cout << s << ' '; }

    return EXIT_SUCCESS;
}
