#include <iostream>
#include <cstdlib>
#include <string>

// return the plural version of word if ctr is greater than 1
std::string make_plural(std::size_t ctr, const std::string &word, const std::string &ending = "s") {
    return (ctr > 1) ? word + ending : word;
}

int main() {
    std::cout << make_plural(1, "success", "es") << '\t';
    std::cout << make_plural(2, "success", "es") << '\n';
    std::cout << make_plural(1, "failure") << '\t';
    std::cout << make_plural(2, "failure") << '\n';

    return 0;
}
