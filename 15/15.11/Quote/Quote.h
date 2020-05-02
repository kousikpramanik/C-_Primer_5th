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

    virtual void debug() const { std::clog << "Quote: bookNo \"" << bookNo << "\", price \"" << price << "\"\n"; }

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

#endif //C_PRIMER_5TH_QUOTE_H
