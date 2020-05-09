#ifndef C_PRIMER_5TH_LIMIT_QUOTE_H
#define C_PRIMER_5TH_LIMIT_QUOTE_H

#include "Disc_quote.h"
#include <string>
#include <cstdlib>
#include <utility>

class Limit_quote : public Disc_quote {
public:
    Limit_quote() = default;

    Limit_quote(std::string book, double p, std::size_t qty, double disc) : Disc_quote(std::move(book), p, qty,
                                                                                       disc) {}

    Limit_quote(const Limit_quote &other) = default;

    Limit_quote &operator=(const Limit_quote &other) = default;

    Limit_quote(Limit_quote &&other) = default;

    Limit_quote &operator=(Limit_quote &&other) = default;

    ~Limit_quote() override = default;

public:
    Limit_quote *clone() const & override { return new Limit_quote(*this); }

    Limit_quote *clone() && override { return new Limit_quote(std::move(*this)); }

public:
    double net_price(std::size_t cnt) const override;
};

inline double Limit_quote::net_price(std::size_t cnt) const {
    if (cnt <= quantity) {
        return cnt * price * (1 - discount);
    } else {
        return net_price(quantity) + (cnt - quantity) * price;
    }
}

#endif //C_PRIMER_5TH_LIMIT_QUOTE_H
