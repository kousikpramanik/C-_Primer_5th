#include <iostream>
#include <vector>
#include <string>
#include "biggies.h"

int main() {
    std::vector<std::string> words;
    for (std::string input; std::cin >> input;) { words.push_back(input); }
    biggies(words, 7);

    return 0;
}
