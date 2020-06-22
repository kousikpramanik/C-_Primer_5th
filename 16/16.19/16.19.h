#ifndef C_PRIMER_5TH_16_19_H
#define C_PRIMER_5TH_16_19_H

#include <iostream>

template<typename C>
void print(C &cont) {
    for (typename C::size_type iter = 0; iter != cont.size(); ++iter) {
        std::cout << cont[iter] << '\n';
    }
}

#endif //C_PRIMER_5TH_16_19_H
