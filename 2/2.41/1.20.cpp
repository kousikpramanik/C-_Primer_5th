#include <iostream>
#include <string>

struct Sales_data {
        std::string ISBN;
        unsigned sale = 0;
        double revenue = 0.0;
};

int main()
{
        Sales_data book;

        double price = 0.0;
        while (std::cin >> book.ISBN >> book.sale >> price) {
                book.revenue = price * book.sale;
                std::cout << book.ISBN << " " << book.sale << " "
                                << book.revenue << " " << price << std::endl;
        }

        return 0;
}
