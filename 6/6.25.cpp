#include <iostream>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <str1> <str2>.\n";
        return -1;
    }

    std::string s(argv[1]);
    s += argv[2];
    std::cout << s << '\n';

    return 0;
}
