#include <iostream>
#include "Quote.h"
#include <utility>
#include "Bulk_quote.h"

void quote_stuff() {
    std::cout << "void quote_stuff()\n";
    Quote q1; // calls Quote::Quote()
    Quote q2("123456", 10); // calls Quote::Quote(std::string book, double sales_price)
    Quote q3(q2); // calls Quote::Quote(const Quote &other)
    Quote q4(std::move(q2)); // calls Quote::Quote(Quote &&other)
    q1 = q3; // calls Quote &Quote::operator=(const Quote &other)
    q2 = std::move(q4); // calls Quote &Quote::operator=(Quote &&other)
} // return from this function calls Quote::~Quote() on each of the four Quote items

void bulk_quote_stuff() {
    std::cout << "void bulk_quote_stuff()\n";
    Bulk_quote q1; // calls Bulk_quote::Bulk_quote(). body executed last, so prints last
    // that calls Disc_quote::Disc_quote()
    // that calls Quote::quote(). body executes first, so prints first
    Bulk_quote q2("123456", 10, 50, 0.1); // similar
    Bulk_quote q3(q2);
    Bulk_quote q4(std::move(q2));
    q1 = q3;
    q2 = std::move(q4);
}

int main() {
    quote_stuff();
    bulk_quote_stuff();
    return 0;
}
