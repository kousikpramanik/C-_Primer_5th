#include <iostream>
#include "Sales_data.h"

int main() {
    Sales_data data1;
    print(std::cout, data1) << '\n'; // will print " 0 0 0"

    Sales_data data2("978-0321992789");
    print(std::cout, data2) << '\n'; // will print "978-0321992789 0 0 0"

    Sales_data data3("978-0321992789", 2, 30);
    print(std::cout, data3) << '\n'; // will print "978-0321992789 2 60 30"

    Sales_data data4(std::cin);
    print(std::cout, data4) << '\n'; // depends on user input

    return 0;
}
