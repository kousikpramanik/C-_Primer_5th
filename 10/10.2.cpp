#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
    std::vector<std::string> haystack;
    std::cout << "Input needle: ";
    std::string needle;
    std::cin >> needle;

    std::cout << "Now input haystack:\n";
    for (std::string input; std::cin >> input;) { haystack.push_back(input); }

    std::cout << "\"" << needle << "\" was found " << std::count(haystack.cbegin(), haystack.cend(), needle)
              << " time(s) in the input.\n";

    return 0;
}
