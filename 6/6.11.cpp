#include <iostream>

void reset(int &n) {
    n = 0;
}

int main() {
    int n = 40;
    std::cout << n << std::endl;
    reset(n);
    std::cout << n << std::endl;

    return 0;
}
