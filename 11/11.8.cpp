#include <map>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

int main() {
    std::map<std::string, std::size_t> word_count;
    std::vector<std::string> exclude{"The", "But", "And", "Or", "An", "A", "the", "but", "and", "or", "an", "a"};
    // problem 1: need to do this manually, or start out with a unique and sorted list
    std::sort(exclude.begin(), exclude.end());
    std::string word;
    while (std::cin >> word) {
        // problem 2: another algorithm instead of a simple member function, though performance might be same for this
        if (std::lower_bound(exclude.cbegin(), exclude.cend(), word) == exclude.cend()) {
            continue;
        }
        ++word_count[word];
    }
    for (const auto &w : word_count) {
        std::cout << w.first << " occurs " << w.second << (w.second == 1 ? " time\n" : " times\n");
    }

    return 0;
}
