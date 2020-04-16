#ifndef C_PRIMER_5TH_SALES_DATA_H
#define C_PRIMER_5TH_SALES_DATA_H

#include <string>

struct Sales_data {
    std::string ISBN;
    unsigned sale = 0;
    double revenue = 0.0;
};

#endif // C_PRIMER_5TH_SALES_DATA_H
