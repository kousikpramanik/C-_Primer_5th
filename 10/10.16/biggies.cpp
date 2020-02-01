#include "biggies.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "elimDups.h"

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz) {
    elimDups(words); // puts words in alphabetical order and remove duplicates
    // sort words by size, but maintain alphabetical order for words of the same size
    std::stable_sort(words.begin(), words.end(),
                     [](const std::string &a, const std::string &b) { return a.size() < b.size(); });
    // get an iterator to the first element whose size() is >=sz
    auto wc = std::find_if(words.begin(), words.end(), [sz](const std::string &a) { return a.size() >= sz; });
    // compute the number of elements with size >= sz
    auto count = words.end() - wc;
    std::cout << count << " word" << (count == 1 ? "" : "s") << " of length " << sz << " or longer.\n";
    // print words of the given size or longer, each one followed by a space
    std::for_each(wc, words.end(), [](const std::string &s) { std::cout << s << ' '; });
    std::cout << '\n';
}
