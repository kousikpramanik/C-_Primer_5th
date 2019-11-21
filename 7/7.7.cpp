#include <iostream>
#include "Sales_data_3.h"

int main() {
    Sales_data total; // variable to hold the running sum
    if (read(std::cin, total)) { // read first transaction
        Sales_data trans; // variable to hold data for the next transaction
        while (read(std::cin, trans)) { // read the remaining transactions
            if (total.isbn() == trans.isbn()) // check the isbns
                total.combine(trans); // update the running total
            else {
                print(std::cout, total) << '\n'; // print the results
                total = trans; // process the next book
            }
        }
        print(std::cout, total) << '\n'; // print the last transaction
    } else { // there was no input
        std::cerr << "No data?!\n"; // notify the user
    }

    return 0;
}
