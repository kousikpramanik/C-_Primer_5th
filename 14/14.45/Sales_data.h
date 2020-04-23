#ifndef C_PRIMER_5TH_SALES_DATA_H
#define C_PRIMER_5TH_SALES_DATA_H

#include <iostream>
#include <string>
#include <utility>

class Sales_data {
    friend std::istream &operator>>(std::istream &is, Sales_data &item);

    friend std::ostream &operator<<(std::ostream &os, const Sales_data &item);

    friend bool operator==(const Sales_data &lhs, const Sales_data &rhs);

public:
    Sales_data() = default;

    explicit Sales_data(std::string s, unsigned n = 0, double p = 0.0) : bookNo(std::move(s)), units_sold(n),
                                                                         revenue(p * n) {}

    explicit Sales_data(std::istream &is) { is >> *this; }

public:
    Sales_data &operator=(std::string isbn);

    Sales_data &operator+=(const Sales_data &other);

public:
    explicit operator std::string() const { return bookNo; }

    explicit operator double() const { return revenue; }

public:
    double avg_price() const;

    std::string isbn() const { return bookNo; }

private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline double Sales_data::avg_price() const {
    if (units_sold != 0) {
        return revenue / units_sold;
    } else {
        return 0;
    }
}

inline Sales_data &Sales_data::operator=(std::string isbn) {
    bookNo = std::move(isbn);
    units_sold = 0;
    revenue = 0.0;
    return *this;
}

inline Sales_data &Sales_data::operator+=(const Sales_data &other) {
    units_sold += other.units_sold;
    revenue += other.revenue;
    return *this;
}

inline std::istream &operator>>(std::istream &is, Sales_data &item) {
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const Sales_data &item) {
    return os << item.bookNo << ' ' << item.units_sold << ' ' << item.revenue << ' ' << item.avg_price();
}

inline Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs) {
    Sales_data temp = lhs;
    temp += rhs;
    return temp;
}

inline bool operator==(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.bookNo == rhs.bookNo && lhs.units_sold == rhs.units_sold && lhs.revenue == rhs.revenue;
}

inline bool operator!=(const Sales_data &lhs, const Sales_data &rhs) { return !(lhs == rhs); }

#endif // C_PRIMER_5TH_SALES_DATA_H
