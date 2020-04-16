#ifndef C_PRIMER_5TH_SALES_DATA_H
#define C_PRIMER_5TH_SALES_DATA_H

#include <iostream>
#include <string>

class Sales_data {
    friend std::istream &read(std::istream &is, Sales_data &item);

    friend std::ostream &print(std::ostream &os, const Sales_data &item);

    friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);

public:
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}

    Sales_data() : Sales_data("", 0, 0.0) {}

    Sales_data(const std::string &s) : Sales_data(s, 0, 0.0) {}

    Sales_data(std::istream &is) : Sales_data() { read(is, *this); }

public:
    Sales_data &combine(const Sales_data &other);

    double avg_price() const;

    std::string isbn() const { return bookNo; }

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline double Sales_data::avg_price() const {
    if (units_sold != 0)
        return revenue / units_sold;
    else
        return 0;
}

std::istream &read(std::istream &is, Sales_data &item);

std::ostream &print(std::ostream &os, const Sales_data &item);

Sales_data add(const Sales_data &lhs, const Sales_data &rhs);

#endif // C_PRIMER_5TH_SALES_DATA_H
