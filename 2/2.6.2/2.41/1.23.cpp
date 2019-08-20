#include <iostream>
#include <string>

struct Sales_data {
        std::string ISBN;
        unsigned sale = 0;
        double revenue = 0.0;
};

int main()
{
        Sales_data running;

        double price = 0.0;
        if (std::cin >> running.ISBN >> running.sale >> price) {
                running.revenue = running.sale * price;
                unsigned count = 1;
                Sales_data curr;
                while (std::cin >> curr.ISBN >> curr.sale >> price) {
                        curr.revenue = curr.sale * price;
                        if (running.ISBN == curr.ISBN) {
                                ++count;
                        } else {
                                std::cout << count << " transaction(s) on ISBN "
                                                << running.ISBN << std::endl;
                                running = curr;
                                count = 1;
                        }
                }
                std::cout << count << " transaction(s) on ISBN " << running.ISBN
                                << std::endl;
                return 0;
        } else {
                std::cerr << "Input is invalid/empty" << std::endl;
                return -1;
        }
}
