#ifndef C_PRIMER_5TH_BASKET_H
#define C_PRIMER_5TH_BASKET_H

#include <memory>
#include "Quote.h"
#include <utility>
#include <iostream>
#include <set>
#include "print_total.h"

class Basket {
public:
    void add_item(const Quote &sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }

    void add_item(Quote &&sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }

    double total_receipt(std::ostream &os) const;

private:
    static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs);

    std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

inline double Basket::total_receipt(std::ostream &os) const {
    double sum = 0.0;
    for (auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter)) {
        sum += print_total(os, **iter, items.count(*iter));
    }
    os << "Total Sale: " << sum << '\n';
    return sum;
}

inline bool Basket::compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) {
    return lhs->isbn() < rhs->isbn();
}

#endif //C_PRIMER_5TH_BASKET_H
