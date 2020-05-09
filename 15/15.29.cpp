#include <vector>
#include <memory>
#include "Quote.h"
#include "Bulk_quote.h"
#include <iostream>

int main() {
    std::vector<std::shared_ptr<Quote>> ptrVect;
    ptrVect.push_back(std::make_shared<Bulk_quote>("123456", 10, 50, 0.1));
    ptrVect.push_back(std::make_shared<Bulk_quote>("567891", 20, 10, 0.5));
    ptrVect.push_back(std::make_shared<Bulk_quote>("784092", 10, 100, 0.1));
    double totalPrice = 0.0;
    for (const auto &q : ptrVect) { totalPrice += q->net_price(100); }
    /*
     * in 15.28, the call to valueVect.push_back() created Bulk_quote temporaries which were then used to initialise
     * Quote objects in the vector. The information about quantity and discount were lost due to slicing.
     *
     * in this case we created objects of type Bulk_quote which were assigned to smart pointers of type Quote. The
     * underlying objects still existed, and the call to net_price was dynamically bound to Bulk_quote::net_price()
     */
    std::cout << totalPrice << '\n';
    return 0;
}
