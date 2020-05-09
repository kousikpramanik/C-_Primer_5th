#ifndef C_PRIMER_5TH_BULK_QUOTE_H
#define C_PRIMER_5TH_BULK_QUOTE_H

#include "Disc_quote.h"
#include <string>
#include <cstdlib>
#include <utility>

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;

    Bulk_quote(std::string book, double p, std::size_t qty, double disc) : Disc_quote(std::move(book), p, qty, disc) {}

    Bulk_quote(const Bulk_quote &other) = default;

    Bulk_quote &operator=(const Bulk_quote &other) = default;

    Bulk_quote(Bulk_quote &&other) = default;

    Bulk_quote &operator=(Bulk_quote &&other) = default;

    ~Bulk_quote() override = default;

public:
    Bulk_quote *clone() const & override { return new Bulk_quote(*this); }

    Bulk_quote *clone() && override { return new Bulk_quote(std::move(*this)); }

public:
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
