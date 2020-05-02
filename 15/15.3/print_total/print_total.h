#ifndef C_PRIMER_5TH_PRINT_TOTAL_H
#define C_PRIMER_5TH_PRINT_TOTAL_H

#include <iostream>
#include "Quote.h"
#include <cstdlib>

inline double print_total(std::ostream &os, const Quote &item, std::size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << '\n';
    return ret;
}

#endif //C_PRIMER_5TH_PRINT_TOTAL_H
