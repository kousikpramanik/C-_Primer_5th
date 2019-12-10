#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data {
    std::string ISBN;
    unsigned sale = 0;
    double revenue = 0.0;
};

#endif
