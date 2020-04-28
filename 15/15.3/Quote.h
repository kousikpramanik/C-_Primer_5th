#ifndef C_PRIMER_5TH_QUOTE_H
#define C_PRIMER_5TH_QUOTE_H

#include <string>
#include <utility>
#include <cstdlib>
#include <iostream>

class Quote {
public:
    Quote() = default;

    Quote(std::string book, double sales_price) : bookNo(std::move(book)), price(sales_price) {}

    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const { return n * price; }

    virtual ~Quote() = default;

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

inline double print_total(std::ostream &os, const Quote &item, size_t n) {
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << '\n';
    return ret;
}

#endif //C_PRIMER_5TH_QUOTE_H
