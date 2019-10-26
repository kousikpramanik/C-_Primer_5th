#include <iostream>
#include <string>
#include <cctype>

int main() {
    std::cout << "Keep entering words." << std::endl;
    bool repeat = false;
    std::string prev;
    std::string input;
    while (std::cin >> input) {
        if (!std::isupper(input[0])) // input.empty() test is unnecessary since >> skips whitespace
            continue;

        if (input == prev) {
            repeat = true;
            std::cout << input << " occurred twice." << std::endl;
            break;
        } else
            prev = input;
    }
    if (!repeat)
        std::cout << "No words were repeated." << std::endl;

    return 0;
}
