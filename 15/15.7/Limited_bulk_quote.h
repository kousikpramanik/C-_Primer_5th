#ifndef C_PRIMER_5TH_LIMITED_BULK_QUOTE_H
#define C_PRIMER_5TH_LIMITED_BULK_QUOTE_H

#include "Bulk_quote.h"
#include <string>
#include <cstdlib>
#include <utility>
#include <stdexcept>

class Limited_bulk_quote : public Bulk_quote {
public:
    Limited_bulk_quote() = default;

    Limited_bulk_quote(std::string book, double p, std::size_t qty_min, std::size_t qty_max, double disc);

    double net_price(std::size_t cnt) const override;

private:
    std::size_t max_qty = 0;
};

inline double Limited_bulk_quote::net_price(std::size_t cnt) const {
    if (cnt <= max_qty) {
        return Bulk_quote::net_price(cnt);
    } else {
        return Bulk_quote::net_price(max_qty) + Quote::net_price(cnt - max_qty);
    }
}

inline Limited_bulk_quote::Limited_bulk_quote(std::string book, double p, std::size_t qty_min, std::size_t qty_max,
                                              double disc) : Bulk_quote(std::move(book), p, qty_min, disc),
                                                             max_qty(qty_max) {
    if (qty_min >= qty_max) { throw std::logic_error("Limited_bulk_quote(): qty_min >= qty_max"); }
}

#endif //C_PRIMER_5TH_LIMITED_BULK_QUOTE_H
