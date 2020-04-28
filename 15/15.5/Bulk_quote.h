#ifndef C_PRIMER_5TH_BULK_QUOTE_H
#define C_PRIMER_5TH_BULK_QUOTE_H

#include "Quote.h"
#include <string>
#include <cstdlib>
#include <utility>

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;

    Bulk_quote(std::string book, double p, std::size_t qty_min, double disc) : Quote(std::move(book), p),
                                                                               min_qty(qty_min), discount(disc) {}

    double net_price(std::size_t cnt) const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

inline double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty) {
        return Quote::net_price(cnt) * (1 - discount);
    } else {
        return Quote::net_price(cnt);
    }
}

#endif //C_PRIMER_5TH_BULK_QUOTE_H
