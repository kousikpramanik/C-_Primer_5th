#include <iostream>

int large(int m, const int *n) {
    if (m > *n)
        return m;
    else
        return *n;
}

int main() {
    int m, n;
    std::cout << "Enter two integers.\n";
    if (std::cin >> m >> n)
        std::cout << large(m, &n) << " is larger.\n";

    return 0;
}
