#ifndef C_PRIMER_5TH_PRINT_H
#define C_PRIMER_5TH_PRINT_H

#include <cstdlib>
#include <iostream>

template<class T, std::size_t N>
void print(const T (&arr)[N]) {
    for (auto &elem : arr) {
        std::cout << elem << '\n';
    }
}

#endif //C_PRIMER_5TH_PRINT_H
