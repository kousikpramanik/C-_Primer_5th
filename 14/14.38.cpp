#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iterator>
#include <algorithm>

class length_test {
public:
    length_test(std::string::size_type l, std::string::size_type u) : lower_bound(l), upper_bound(u) {}

    bool operator()(const std::string &test) const {
        auto length = test.length();
        return length >= lower_bound && length <= upper_bound;
    }

private:
    std::string::size_type lower_bound;
    std::string::size_type upper_bound;
};

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
    std::istream_iterator<std::string> inp_iter(inp), inp_end;
    auto in_bound_count = std::count_if(inp_iter, inp_end, length_test(1, 10));
    std::cout << in_bound_count << " words in \"" << argv[1] << "\" are of sizes 1 through 10.\n";

    return EXIT_SUCCESS;
}
