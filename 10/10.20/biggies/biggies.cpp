#include "biggies.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "elimDups.h"

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    std::stable_sort(words.begin(), words.end(),
                     [](const std::string &a, const std::string &b) { return a.size() < b.size(); });
    auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string &s) { return s.length() >= sz; });
    auto count = std::count_if(words.begin(), words.end(), [sz](const std::string &s) { return s.length() >= sz; });
    std::cout << count << " word" << (count == 1 ? "" : "s") << " of length " << sz << " or longer.\n";
    std::for_each(wc, words.end(), [](const std::string &s) { std::cout << s << ' '; });
    std::cout << '\n';
}
