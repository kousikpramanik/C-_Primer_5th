#include "Quote.h"
#include "Bulk_quote.h"
#include "print_total.h"
#include <iostream>

int main() {
    Quote q("123456", 5);
    Bulk_quote bq("123456", 5, 50, 0.10);

    print_total(std::cout, q, 25);
    print_total(std::cout, bq, 25);
    print_total(std::cout, q, 50);
    print_total(std::cout, bq, 50);
    print_total(std::cout, q, 100);
    print_total(std::cout, bq, 100);

    return 0;
}
