#include <iostream>
#include <string>

void prefix_name_suffix(std::string &name, const std::string &prefix, const std::string &suffix) {
    name.insert(name.begin(), 1, ' ');
    name.insert(name.begin(), prefix.cbegin(), prefix.cend());
    name.append(1, ' ');
    name.append(suffix);
}

int main() {
    std::string test("Stephen Inverter");
    prefix_name_suffix(test, "Mr.", "III");
    std::cout << test << '\n';

    return 0;
}
