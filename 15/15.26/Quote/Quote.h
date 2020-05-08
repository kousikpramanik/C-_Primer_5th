#ifndef C_PRIMER_5TH_QUOTE_H
#define C_PRIMER_5TH_QUOTE_H

#include <iostream>
#include <string>
#include <utility>
#include <cstdlib>

class Quote {
public:
    Quote() { std::cout << "Quote::Quote()\n"; }

    Quote(std::string book, double sales_price);

    Quote(const Quote &other);

    Quote &operator=(const Quote &other);

    Quote(Quote &&other);

    Quote &operator=(Quote &&other);

    virtual ~Quote() { std::cout << "Quote::~Quote()\n"; }

public:
    std::string isbn() const { return bookNo; }

    virtual double net_price(std::size_t n) const { return n * price; }

private:
    std::string bookNo;
protected:
    double price = 0.0;
};

inline Quote::Quote(std::string book, double sales_price) : bookNo(std::move(book)), price(sales_price) {
    std::cout << "Quote::Quote(std::string book, double sales_price)\n";
}

inline Quote::Quote(const Quote &other) : bookNo(other.bookNo), price(other.price) {
    std::cout << "Quote::Quote(const Quote &other)\n";
}

inline Quote &Quote::operator=(const Quote &other) {
    std::cout << "Quote &Quote::operator=(const Quote &other)\n";
    bookNo = other.bookNo;
    price = other.price;
    return *this;
}

inline Quote::Quote(Quote &&other) : bookNo(std::move(other.bookNo)), price(other.price) {
    std::cout << "Quote::Quote(Quote &&other)\n";
}

inline Quote &Quote::operator=(Quote &&other) {
    std::cout << "Quote &Quote::operator=(Quote &&other)\n";
    bookNo = std::move(other.bookNo);
    price = other.price;
    return *this;
}

#endif //C_PRIMER_5TH_QUOTE_H
