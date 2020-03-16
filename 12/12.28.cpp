#include <fstream>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <sstream>

void runQueries(std::ifstream &infile);

void store(std::ifstream &infile, std::vector<std::string> &text,
           std::map<std::string, std::multiset<std::vector<std::string>::size_type>> &wordmap);

std::ostream &print(std::ostream &os, const std::string &s,
                    const std::vector<std::string> &text,
                    const std::map<std::string, std::multiset<std::vector<std::string>::size_type>> &wordmap);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "USAGE: " << argv[0] << " <INPUTFILE>\n";
        return EXIT_FAILURE;
    }
    std::ifstream infile(argv[1]);
    if (!infile) {
        std::cerr << "Failed to open \"" << argv[1] << "\".\n";
        return EXIT_FAILURE;
    }

    runQueries(infile);

    return EXIT_SUCCESS;
}

void runQueries(std::ifstream &infile) {
    std::vector<std::string> text;
    std::map<std::string, std::multiset<std::vector<std::string>::size_type>> wordmap;
    store(infile, text, wordmap);

    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, s, text, wordmap) << '\n';
    }
}

void store(std::ifstream &infile, std::vector<std::string> &text,
           std::map<std::string, std::multiset<std::vector<std::string>::size_type>> &wordmap) {
    std::string input;
    for (std::vector<std::string>::size_type linenum = 0; std::getline(infile, input); ++linenum) {
        text.push_back(input);
        std::istringstream inputstream(input);
        for (std::string word; inputstream >> word;) { wordmap[word].insert(linenum); }
    }
}

std::ostream &print(std::ostream &os, const std::string &s,
                    const std::vector<std::string> &text,
                    const std::map<std::string, std::multiset<std::vector<std::string>::size_type>> &wordmap) {
    auto places = wordmap.find(s);
    if (places != wordmap.end()) {
        for (auto iter = places->second.cbegin();
             iter != places->second.cend(); iter = places->second.upper_bound(*iter)) {
            std::cout << "Line " << *iter + 1 << ": " << text[*iter] << '\n';
        }
        std::cout << "Word \"" << s << "\" occurred " << places->second.size() << " times.";
    } else {
        os << "Word \"" << s << "\" not found.";
    }

    return os;
}
