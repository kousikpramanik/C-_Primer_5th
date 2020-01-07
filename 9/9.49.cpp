#include <iostream>
#include <string>
#include <sstream>

int main() {
    const std::string ascenderDescender("bdfghijklpqty");
    std::string longest;

    std::cout << "Enter some words. Blank line to finish.\n";
    for (std::string inputCin; std::getline(std::cin, inputCin) && !inputCin.empty();) {
        std::istringstream inpStream(inputCin);
        for (std::string input; inpStream >> input;) {
            if (input.find_first_of(ascenderDescender) == std::string::npos && input.length() > longest.length()) {
                longest = input;
            }
        }
    }
    std::cout << '\"' << longest << '\"' << " was the longest string lacking ascenders or descenders.\n";

    return 0;
}
