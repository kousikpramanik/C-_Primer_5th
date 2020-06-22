#ifndef C_PRIMER_5TH_16_20_H
#define C_PRIMER_5TH_16_20_H

#include <iostream>

template<typename C>
void print(C &cont) {
    for (typename C::const_iterator iter = cont.cbegin(); iter != cont.cend(); ++iter) {
        std::cout << *iter << '\n';
    }
}

#endif //C_PRIMER_5TH_16_20_H
