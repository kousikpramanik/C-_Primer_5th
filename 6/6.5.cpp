#include <iostream>

int mod(const int &n) {
    return n >= 0 ? n : -n;
}

int main() {
    std::cout << "|5| is " << mod(5) << std::endl;
    std::cout << "|-5| is " << mod(-5) << std::endl;

    return 0;
}
