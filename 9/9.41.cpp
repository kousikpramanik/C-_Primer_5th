#include <vector>
#include <string>
#include <iostream>

int main() {
    std::vector<char> chvec{'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!'};
    std::string fromvec(chvec.cbegin(), chvec.cend());

    for (char ch : chvec) {
        std::cout << ch;
    }
    std::cout << '\n';

    std::cout << fromvec << '\n';

    return 0;
}
