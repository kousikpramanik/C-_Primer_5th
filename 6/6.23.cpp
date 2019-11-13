#include <iostream>
#include <cstddef>
#include <iterator>

// only these two can be used to print both i and j
void print1(const int *beg, const int *end) {
    while (beg != end)
        std::cout << *beg++ << std::endl;
}

void print2(const int ia[], std::size_t size) {
    for (size_t i = 0; i != size; ++i)
        std::cout << ia[i] << std::endl;
}

int main() {
    int i = 0;
    int j[2] = {0, 1};

    print1(&i, &i + 1);
    print2(&i, 1);

    print1(std::begin(j), std::end(j));
    print2(j, 2);
}
