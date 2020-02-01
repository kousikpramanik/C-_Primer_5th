#include "biggies.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "elimDups.h"

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    auto szNot = std::stable_partition(words.begin(), words.end(),
                                       [sz](const std::string &a) { return a.size() >= sz; });
    auto count = szNot - words.begin();
    std::cout << count << " word" << (count == 1 ? "" : "s") << " of length " << sz << " or longer.\n";
    std::for_each(words.begin(), szNot, [](const std::string &s) { std::cout << s << ' '; });
    std::cout << '\n';
}
