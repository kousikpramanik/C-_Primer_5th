#ifndef C_PRIMER_5TH_BULK_QUOTE_H
#define C_PRIMER_5TH_BULK_QUOTE_H

#include "Disc_quote.h"
#include <string>
#include <cstdlib>
#include <utility>

class Bulk_quote : public Disc_quote {
public:
    using Disc_quote::Disc_quote;

    double net_price(std::size_t cnt) const override;
};

inline double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= quantity) {
        return cnt * price * (1 - discount);
    } else {
        return cnt * price;
    }
}

#endif //C_PRIMER_5TH_BULK_QUOTE_H
