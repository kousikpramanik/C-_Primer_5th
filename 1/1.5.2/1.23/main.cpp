#include <iostream>
#include "Sales_item.h"

int main()
{
        Sales_item running;

        if (std::cin >> running) {
                int count = 1;
                Sales_item curr;
                while (std::cin >> curr) {
                        if (running.isbn() == curr.isbn())
                                ++count;
                        else {
                                std::cout << count << " transaction(s) on ISBN "
                                                << running.isbn() << std::endl;
                                running = curr;
                                count = 1;
                        }
                }
                std::cout << count << " transaction(s) on ISBN "
                                << running.isbn() << std::endl;
                return 0;
        } else {
                std::cerr << "Input is invalid/empty" << std::endl;
                return -1;
        }
}
