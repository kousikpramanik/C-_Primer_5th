#ifndef C_PRIMER_5TH_DISC_QUOTE_H
#define C_PRIMER_5TH_DISC_QUOTE_H

#include "Quote.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>

class Disc_quote : public Quote {
public:
    Disc_quote() { std::cout << "Disc_quote::Disc_quote()\n"; }

    Disc_quote(std::string book, double price, std::size_t qty, double disc);

    Disc_quote(const Disc_quote &other);

    Disc_quote &operator=(const Disc_quote &other);

    Disc_quote(Disc_quote &&other);

    Disc_quote &operator=(Disc_quote &&other);

    ~Disc_quote() override { std::cout << "Disc_quote::~Disc_quote()\n"; }

public:
    double net_price(std::size_t) const override = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};

inline Disc_quote::Disc_quote(std::string book, double price, std::size_t qty, double disc) :
        Quote(std::move(book), price), quantity(qty), discount(disc) {
    std::cout << "Disc_quote::Disc_quote(std::string book, double price, std::size_t qty, double disc)\n";
}

inline Disc_quote::Disc_quote(const Disc_quote &other) :
        Quote(other), quantity(other.quantity), discount(other.discount) {
    std::cout << "Disc_quote::Disc_quote(const Disc_quote &other)\n";
}

inline Disc_quote &Disc_quote::operator=(const Disc_quote &other) {
    std::cout << "Disc_quote &Disc_quote::operator=(const Disc_quote &other)\n";
    Quote::operator=(other);
    quantity = other.quantity;
    discount = other.discount;
    return *this;
}

inline Disc_quote::Disc_quote(Disc_quote &&other) :
        Quote(std::move(other)), quantity(other.quantity), discount(other.discount) {
    std::cout << "Disc_quote::Disc_quote(Disc_quote &&other)\n";
}

inline Disc_quote &Disc_quote::operator=(Disc_quote &&other) {
    std::cout << "Disc_quote &Disc_quote::operator=(Disc_quote &&other)\n";
    Quote::operator=(std::move(other));
    quantity = other.quantity;
    discount = other.discount;
    return *this;
}

#endif //C_PRIMER_5TH_DISC_QUOTE_H
