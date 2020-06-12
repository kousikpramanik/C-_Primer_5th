#ifndef C_PRIMER_5TH_TNX_PROC_H
#define C_PRIMER_5TH_TNX_PROC_H

#include <iostream>
#include <string>
#include "Sales_data.h"

std::istream &read(std::istream &stream, Sales_data &obj);

std::ostream &print(std::ostream &stream, const Sales_data &obj);

Sales_data &combine(Sales_data &lhs, const Sales_data &rhs);

double avg_price(const Sales_data &obj);

inline const std::string &isbn(const Sales_data &obj) {
    return obj.ISBN;
}

#endif //C_PRIMER_5TH_TNX_PROC_H
