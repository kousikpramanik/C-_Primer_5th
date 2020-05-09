#ifndef C_PRIMER_5TH_DISC_QUOTE_H
#define C_PRIMER_5TH_DISC_QUOTE_H

#include "Quote.h"
#include <string>
#include <cstdlib>
#include <utility>

class Disc_quote : public Quote {
public:
    Disc_quote() = default;

    Disc_quote(std::string book, double price, std::size_t qty, double disc) : Quote(std::move(book), price),
                                                                               quantity(qty), discount(disc) {}

    Disc_quote(const Disc_quote &other) = default;

    Disc_quote &operator=(const Disc_quote &other) = default;

    Disc_quote(Disc_quote &&other) = default;

    Disc_quote &operator=(Disc_quote &&other) = default;

    ~Disc_quote() override = default;

public:
    double net_price(std::size_t) const override = 0;

    std::pair<std::size_t, double> discount_policy() const { return std::make_pair(quantity, discount); }

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

#endif //C_PRIMER_5TH_DISC_QUOTE_H
