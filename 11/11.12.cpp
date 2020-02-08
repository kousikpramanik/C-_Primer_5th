#include <vector>
#include <utility>
#include <string>
#include <iostream>

int main() {
    std::vector<std::pair<std::string, int>> strIntVec;
    {
        std::string first;
        int second;
        while (std::cin >> first >> second) { strIntVec.emplace_back(first, second); }
    }
    for (const auto &pair : strIntVec) { std::cout << pair.first << ' ' << pair.second << '\n'; }

    return 0;
}
