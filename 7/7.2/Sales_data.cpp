#include "Sales_data.h"

Sales_data &Sales_data::combine(const Sales_data &other) {
    units_sold += other.units_sold;
    revenue += other.revenue;

    return *this;
}
