#include <iostream>
#include <cstdlib>
#include <fstream>
#include "TextQuery.h"
#include <vector>
#include "Query.h"
#include <string>
#include "Query_parser.h"
#include <utility>
#include <stdexcept>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " [FILE]\n";
        return EXIT_FAILURE;
    }
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Failed to open \"" << argv[1] << "\".\n";
        return EXIT_FAILURE;
    }
    TextQuery tq(infile);
    std::vector<Query> history;
    std::string current_string;
    std::cout << R"(A '\' at the beginning followed by an integer causes history expansion.
Anything else causes the '\' at the beginning to be ignored.
Type your query: )";
    while (std::getline(std::cin, current_string) && !current_string.empty()) {
        try {
            auto current_query = strToQuery(current_string, history);
            print(std::cout, current_query.eval(tq));
            history.push_back(std::move(current_query));
        } catch (const std::invalid_argument &err) {
            std::cout << err.what() << '\n';
        } catch (const std::out_of_range &err) {
            std::cout << "Invalid history expansion attempt!\n";
        }
        std::cout << "Type your query (Empty line to quit): ";
    }

    return EXIT_SUCCESS;
}
