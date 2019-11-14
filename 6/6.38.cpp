#include <iostream>

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

// returns a reference to an array of five int elements
decltype(odd) &arrPtr(int i) {
    return (i % 2) ? odd : even; // returns a reference to the array
}

int main(void) {
    decltype(odd) &one = arrPtr(1);
    for (auto n : one)
        std::cout << n << '\t';
    std::cout << '\n';

    decltype(odd) &two = arrPtr(2);
    for (auto n : two)
        std::cout << n << '\t';
    std::cout << '\n';
}
