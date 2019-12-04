#ifndef SALES_DATA_2_H_
#define SALES_DATA_2_H_

#include <string>

struct Sales_data {
    std::string isbn() const { return bookNo; }

    Sales_data &combine(const Sales_data &other);

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

#endif
