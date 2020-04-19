#include "biggies.h"

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "elimDups.h"

class size_check {
public:
    explicit size_check(std::vector<std::string>::size_type n) : sz(n) {}

    bool operator()(const std::string &s) const { return s.size() >= sz; }

private:
    std::vector<std::string>::size_type sz;
};

class print_cout {
public:
    void operator()(const std::string &s) const { std::cout << s << ' '; }
};

void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz) {
    elimDups(words);
    auto szNot = std::partition(words.begin(), words.end(), size_check(sz));
    auto count = szNot - words.begin();
    std::cout << count << " word" << (count == 1 ? "" : "s") << " of length " << sz << " or longer.\n";
    std::for_each(words.begin(), szNot, print_cout());
    std::cout << '\n';
}
