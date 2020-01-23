#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> haystack;
    std::cout << "Input needle: ";
    int needle;
    std::cin >> needle;

    std::cout << "Now input haystack:\n";
    for (int input; std::cin >> input;) { haystack.push_back(input); }

    std::cout << needle << " was found " << std::count(haystack.cbegin(), haystack.cend(), needle)
              << " time(s) in the input.\n";

    return 0;
}
