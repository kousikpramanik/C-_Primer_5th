// obviously just use subscripts. what even is this first, second mumbo jumbo. requires extra typing too.

#include <map>
#include <string>
#include <cstdlib>
#include <iostream>

int main() {
    std::map<std::string, std::size_t> word_count;
    std::string word;
    while (std::cin >> word) {
        auto insert_success = word_count.emplace(word, 1);
        if (!insert_success.second) { ++(insert_success.first)->second; }
    }
    for (const auto &w : word_count) {
        std::cout << w.first << " occurs " << w.second << (w.second == 1 ? " time\n" : " times\n");
    }

    return 0;
}
