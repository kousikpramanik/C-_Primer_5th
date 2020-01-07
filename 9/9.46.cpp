#include <iostream>
#include <string>

void prefix_name_suffix(std::string &name, const std::string &prefix, const std::string &suffix) {
    name.insert(0, 1, ' ');
    name.insert(0, prefix);
    name.insert(name.length(), 1, ' ');
    name.insert(name.length(), suffix);
}

int main() {
    std::string test("Stephen Inverter");
    prefix_name_suffix(test, "Mr.", "III");
    std::cout << test << '\n';

    return 0;
}
