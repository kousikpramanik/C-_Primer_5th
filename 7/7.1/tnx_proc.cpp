#include "tnx_proc.h"

#include <iostream>
#include "Sales_data.h"

std::istream &read(std::istream &stream, Sales_data &obj) {
    double price = 0;
    stream >> obj.ISBN >> obj.sale >> price;
    obj.revenue = price * obj.sale;

    return stream;
}

std::ostream &print(std::ostream &stream, const Sales_data &obj) {
    stream << obj.ISBN << ' ' << obj.sale << ' ' << obj.revenue << ' ' << avg_price(obj);

    return stream;
}

Sales_data &combine(Sales_data &lhs, const Sales_data &rhs) {
    lhs.sale += rhs.sale;
    lhs.revenue += rhs.revenue;
    return lhs;
}

double avg_price(const Sales_data &obj) {
    if (obj.sale != 0)
        return obj.revenue / obj.sale;
    else
        return 0;
}
