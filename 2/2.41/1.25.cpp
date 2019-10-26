#include <iostream>
#include <string>

struct Sales_data {
    std::string ISBN;
    unsigned sale = 0;
    double revenue = 0.0;
};

int main() {
    Sales_data total; // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    double price = 0.0;
    if (std::cin >> total.ISBN >> total.sale >> price) {
        total.revenue = total.sale * price;
        Sales_data trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (std::cin >> trans.ISBN >> trans.sale >> price) {
            trans.revenue = trans.sale * price;
            // if we're still processing the same book
            if (total.ISBN == trans.ISBN) {
                total.sale += trans.sale; // update the running total
                total.revenue += trans.revenue;
            } else {
                // print results for the previous book
                std::cout << total.ISBN << " " << total.sale << " " << total.revenue << " ";
                if (total.sale != 0)
                    std::cout << total.revenue / total.sale << std::endl;
                else
                    std::cout << "(no sale)" << std::endl;
                total = trans;
            }
        }
        std::cout << total.ISBN << " " << total.sale << " " << total.revenue << " "; // print the last transaction
        if (total.sale != 0)
            std::cout << total.revenue / total.sale << std::endl;
        else
            std::cout << "(no sale)" << std::endl;

        return 0;
    } else {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1; // indicate failure
    }
}
