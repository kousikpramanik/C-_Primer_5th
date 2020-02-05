#include "biggies.h"

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "elimDups.h"

bool check_size(const std::string &s, std::string::size_type sz) { return s.length() >= sz; }

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    auto szNot = std::stable_partition(words.begin(), words.end(), std::bind(check_size, std::placeholders::_1, sz));
    auto count = szNot - words.begin();
    std::cout << count << " word" << (count == 1 ? "" : "s") << " of length " << sz << " or longer.\n";
    std::for_each(words.begin(), szNot, [](const std::string &s) { std::cout << s << ' '; });
    std::cout << '\n';
}
