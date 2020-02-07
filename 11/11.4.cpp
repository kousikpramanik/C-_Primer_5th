#include <map>
#include <string>
#include <cstdlib>
#include <set>
#include <iostream>
#include <algorithm>
#include <cctype>

int main() {
    std::map<std::string, std::size_t> word_count;
    std::set<std::string> exclude{"the", "but", "and", "or", "an", "a"};
    std::string word;
    while (std::cin >> word) {
        for (auto &c : word) { c = std::tolower(c); }
        word.erase(std::remove_if(word.begin(), word.end(), static_cast<int (*)(int)>(std::ispunct)), word.end());
        if (exclude.find(word) == exclude.end()) { ++word_count[word]; }
    }
    for (const auto &w : word_count) {
        std::cout << w.first << " occurs " << w.second << (w.second == 1 ? " time\n" : " times\n");
    }

    return 0;
}
