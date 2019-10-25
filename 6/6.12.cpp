#include <iostream>

void swap(int &a, int &b) {
    auto temp = b;
    b = a;
    a = temp;
}

int main() {
    int i = 3;
    int j = 5;
    std::cout << i << ' ' << j << std::endl;
    swap(i, j);
    std::cout << i << ' ' << j << std::endl;

    return 0;
}
