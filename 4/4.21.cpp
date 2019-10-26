#include <iostream>
#include <vector>

int main() {
    std::vector<int> vect;

    std::cout << "Enter integers (EOF/invalid input to stop)." << std::endl;
    for (int temp; std::cin >> temp;)
        vect.push_back(temp);

    std::cout << "Here is the vector: ";
    for (const auto &n: vect)
        std::cout << n << ' ';
    std::cout << std::endl;

    std::cout << "Now doubling odd values." << std::endl;
    for (auto &n : vect)
        n % 2 ? n *= 2 : n; // a ?: b; is a gcc special feature.

    std::cout << "Here is the vector again: ";
    for (const auto &n : vect)
        std::cout << n << ' ';
    std::cout << std::endl;

    return 0;
}
