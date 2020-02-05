#include "biggies.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include "elimDups.h"

bool isShorter(const std::string &a, const std::string &b) { return a.size() < b.size(); }

bool sizeComp(const std::string &s, std::string::size_type sz) { return s.length() >= sz; }

void print(const std::string &s) { std::cout << s << ' '; }

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(), isShorter);
    auto wc = std::find_if(words.begin(), words.end(), std::bind(sizeComp, std::placeholders::_1, sz));
    auto count = std::count_if(words.begin(), words.end(), std::bind(sizeComp, std::placeholders::_1, sz));
    std::cout << count << " word" << (count == 1 ? "" : "s") << " of length " << sz << " or longer.\n";
    std::for_each(wc, words.end(), print);
    std::cout << '\n';
}
