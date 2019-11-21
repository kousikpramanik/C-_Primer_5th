#include "tnx_proc_2.h"

#include <iostream>
#include "Sales_data_2.h"

std::istream &read(std::istream &stream, Sales_data &obj) {
    double price = 0;
    stream >> obj.bookNo >> obj.units_sold >> price;
    obj.revenue = price * obj.units_sold;

    return stream;
}

std::ostream &print(std::ostream &stream, const Sales_data &obj) {
    stream << obj.bookNo << ' ' << obj.units_sold << ' ' << obj.revenue << ' ' << avg_price(obj);

    return stream;
}

double avg_price(const Sales_data &obj) {
    if (obj.units_sold != 0)
        return obj.revenue / obj.units_sold;
    else
        return 0;
}
