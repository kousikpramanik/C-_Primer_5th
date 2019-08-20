#include <iostream>
#include <string>
#include "Sales_data.h"

int main()
{
        Sales_data book, temp;

        double price = 0.0;
        std::cin >> book.ISBN >> book.sale >> price;
        book.revenue = price * book.sale;
        std::cin >> temp.ISBN >> temp.sale >> price;
        temp.revenue = price * temp.sale;

        if (book.ISBN == temp.ISBN) {
                book.sale += temp.sale;
                book.revenue += temp.revenue;
                std::cout << book.ISBN << " " << book.sale << " "
                                << book.revenue << " ";

                if (book.sale != 0)
                        std::cout << book.revenue / book.sale << std::endl;
                else
                        std::cout << "(no sale)" << std::endl;

                return 0;
        } else {
                std::cerr << "Data must refer to the same ISBN" << std::endl;
                return -1;
        }
}
