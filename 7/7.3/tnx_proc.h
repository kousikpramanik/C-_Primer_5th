#ifndef C_PRIMER_5TH_TNX_PROC_H
#define C_PRIMER_5TH_TNX_PROC_H

#include <iostream>
#include "Sales_data.h"

std::istream &read(std::istream &stream, Sales_data &obj);

std::ostream &print(std::ostream &stream, const Sales_data &obj);

double avg_price(const Sales_data &obj);

#endif // C_PRIMER_5TH_TNX_PROC_H
