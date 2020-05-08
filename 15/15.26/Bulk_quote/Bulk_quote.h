#ifndef C_PRIMER_5TH_BULK_QUOTE_H
#define C_PRIMER_5TH_BULK_QUOTE_H

#include "Disc_quote.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <utility>

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() { std::cout << "Bulk_quote::Bulk_quote()\n"; }

    Bulk_quote(std::string book, double p, std::size_t qty, double disc);

    Bulk_quote(const Bulk_quote &other);

    Bulk_quote &operator=(const Bulk_quote &other);

    Bulk_quote(Bulk_quote &&other);

    Bulk_quote &operator=(Bulk_quote &&other);

    ~Bulk_quote() override { std::cout << "Bulk_quote::~Bulk_quote()\n"; }

public:
    double net_price(std::size_t cnt) const override;
};

inline Bulk_quote::Bulk_quote(std::string book, double p, std::size_t qty, double disc) : Disc_quote(std::move(book), p,
                                                                                                     qty, disc) {
    std::cout << "Bulk_quote::Bulk_quote(std::string book, double p, std::size_t qty, double disc)\n";
}

inline Bulk_quote::Bulk_quote(const Bulk_quote &other) : Disc_quote(other) {
    std::cout << "Bulk_quote::Bulk_quote(const Bulk_quote &other)\n";
}

inline Bulk_quote &Bulk_quote::operator=(const Bulk_quote &other) {
    std::cout << "Bulk_quote &Bulk_quote::operator=(const Bulk_quote &other)\n";
    Disc_quote::operator=(other);
    return *this;
}

inline Bulk_quote::Bulk_quote(Bulk_quote &&other) : Disc_quote(std::move(other)) {
    std::cout << "Bulk_quote::Bulk_quote(Bulk_quote &&other)\n";
}

inline Bulk_quote &Bulk_quote::operator=(Bulk_quote &&other) {
    std::cout << "Bulk_quote &Bulk_quote::operator=(Bulk_quote &&other)\n";
    Disc_quote::operator=(std::move(other));
    return *this;
}

inline double Bulk_quote::net_price(std::size_t cnt) const {
    if (cnt >= quantity) {
        return cnt * price * (1 - discount);
    } else {
        return cnt * price;
    }
}

#endif //C_PRIMER_5TH_BULK_QUOTE_H
