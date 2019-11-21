#ifndef TNX_PROC_2_H_
#define TNX_PROC_2_H_

#include <iostream>
#include "Sales_data_2.h"

std::istream &read(std::istream &stream, Sales_data &obj);

std::ostream &print(std::ostream &stream, const Sales_data &obj);

double avg_price(const Sales_data &obj);

#endif
