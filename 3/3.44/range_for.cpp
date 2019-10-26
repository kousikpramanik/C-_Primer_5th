#include <iostream>

int main() {
    int ia[3][4] = {
            {0, 1, 2,  3},
            {4, 5, 6,  7},
            {8, 9, 10, 11}
    };

    using int_array_ref = const int (&)[4];
    using int_ref = const int &;

    for (int_array_ref row : ia) {
        for (int_ref col : row)
            std::cout << col << ' ';
        std::cout << std::endl;
    }

    return 0;
}
