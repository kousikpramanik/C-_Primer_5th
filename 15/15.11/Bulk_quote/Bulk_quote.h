#ifndef C_PRIMER_5TH_BULK_QUOTE_H
#define C_PRIMER_5TH_BULK_QUOTE_H

#include "Quote.h"
#include <string>
#include <cstdlib>
#include <utility>
#include <iostream>

class Bulk_quote : public Quote {
public:
    Bulk_quote() = default;

    Bulk_quote(std::string book, double p, std::size_t qty, double disc) : Quote(std::move(book), p), min_qty(qty),
                                                                           discount(disc) {}

    double net_price(std::size_t cnt) const override;

    void debug() const override;

private:
    std::size_t min_qty = 0;
    double discount = 0.0;
};

inline double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= min_qty) {
        return cnt * price * (1 - discount);
    } else {
        return cnt * price;
    }
}

inline void Bulk_quote::debug() const {
    std::clog << "Bulk_quote: min_qty \"" << min_qty << "\", discount \"" << discount << "\"\n";
}

#endif //C_PRIMER_5TH_BULK_QUOTE_H
