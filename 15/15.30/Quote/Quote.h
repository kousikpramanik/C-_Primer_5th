#ifndef C_PRIMER_5TH_QUOTE_H
#define C_PRIMER_5TH_QUOTE_H

#include <string>
#include <utility>
#include <cstdlib>

class Quote {
public:
    Quote() = default;

    Quote(std::string book, double sales_price) : bookNo(std::move(book)), price(sales_price) {}

    Quote(const Quote &other) = default;

    Quote &operator=(const Quote &other) = default;

    Quote(Quote &&other) = default;

    Quote &operator=(Quote &&other) = default;

    virtual ~Quote() = default;

public:
    virtual Quote *clone() const &{ return new Quote(*this); }

    virtual Quote *clone() &&{ return new Quote(std::move(*this)); }

public:
    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const { return n * price; }

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

#endif //C_PRIMER_5TH_QUOTE_H
