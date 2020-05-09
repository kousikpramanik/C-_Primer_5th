#include "Basket.h"
#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include <iostream>

int main() {
    Basket saleData;
    for (auto i = 0; i != 5; ++i) { saleData.add_item(Quote("202031", 10)); }
    for (auto i = 0; i != 100; ++i) { saleData.add_item(Bulk_quote("123456", 10, 50, 0.1)); }
    for (auto i = 0; i != 20; ++i) { saleData.add_item(Limit_quote("341094", 10, 10, 0.5)); }
    saleData.total_receipt(std::cout);

    return 0;
}
