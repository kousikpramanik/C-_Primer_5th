#include "Sales_data_5.h"

#include <iostream>

Sales_data &Sales_data::combine(const Sales_data &other) {
    units_sold += other.units_sold;
    revenue += other.revenue;

    return *this;
}

double Sales_data::avg_price() const {
    if (units_sold != 0)
        return revenue / units_sold;
    else
        return 0;
}

std::istream &read(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;

    return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item) {
    os << item.bookNo << ' ' << item.units_sold << ' ' << item.revenue << ' ' << item.avg_price();

    return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data temp = lhs;
    temp.units_sold += rhs.units_sold;
    temp.revenue += rhs.revenue;

    return temp;
}
