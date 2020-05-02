#ifndef C_PRIMER_5TH_LIMIT_QUOTE_H
#define C_PRIMER_5TH_LIMIT_QUOTE_H

#include "Quote.h"
#include <string>
#include <cstdlib>
#include <utility>
#include <iostream>

class Limit_quote : public Quote {
public:
    Limit_quote() = default;

    Limit_quote(std::string book, double p, std::size_t qty, double disc) : Quote(std::move(book), p), max_qty(qty),
                                                                            discount(disc) {}

    double net_price(std::size_t cnt) const override;

    void debug() const override;

private:
    std::size_t max_qty = 0;
    double discount = 0.0;
};

inline double Limit_quote::net_price(std::size_t cnt) const {
    if (cnt <= max_qty) {
        return cnt * price * (1 - discount);
    } else {
        return net_price(max_qty) + (cnt - max_qty) * price;
    }
}

inline void Limit_quote::debug() const {
    std::clog << "Limit_quote: max_qty \"" << max_qty << "\", discount \"" << discount << "\"\n";
}

#endif //C_PRIMER_5TH_LIMIT_QUOTE_H
