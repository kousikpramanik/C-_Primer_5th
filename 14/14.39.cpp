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
    length_test bounds(1, 9);
    std::string::size_type in_one_nine = 0, ten_or_more = 0;
    for (std::istream_iterator<std::string> inp_iter(inp), inp_end; inp_iter != inp_end; ++inp_iter) {
        if (bounds(*inp_iter)) {
            ++in_one_nine;
        } else {
            ++ten_or_more;
        }
    }
    std::cout << in_one_nine << " words in \"" << argv[1] << "\" are of sizes 1 through 9.\n";
    std::cout << ten_or_more << " words in \"" << argv[1] << "\" are of sizes 10 or more.\n";

    return EXIT_SUCCESS;
}
