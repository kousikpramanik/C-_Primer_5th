#include <vector>
#include "Quote.h"
#include "Bulk_quote.h"
#include <iostream>

int main() {
    std::vector<Quote> valueVect;
    valueVect.push_back(Bulk_quote("123456", 10, 50, 0.1));
    valueVect.push_back(Bulk_quote("567891", 20, 10, 0.5));
    valueVect.push_back(Bulk_quote("784092", 10, 100, 0.1));
    double totalPrice = 0.0;
    for (const auto &q : valueVect) { totalPrice += q.net_price(100); }
    std::cout << totalPrice << '\n';
    return 0;
}
