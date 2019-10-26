#include <iostream>
#include <string>

struct Sales_data {
    std::string ISBN;
    unsigned sale = 0;
    double revenue = 0.0;
};

int main() {
    Sales_data book;

    double price = 0.0;
    if (std::cin >> book.ISBN >> book.sale >> price) {
        book.revenue = book.sale * price;
        Sales_data temp;
        while (std::cin >> temp.ISBN >> temp.sale >> price) {
            temp.revenue = temp.sale * price;
            if (book.ISBN == temp.ISBN) {
                book.sale += temp.sale;
                book.revenue += temp.revenue;
            } else {
                std::cerr << "Entries must refer to the same ISBN" << std::endl;
                break;
            }
        }
    }

    std::cout << book.ISBN << " " << book.sale << " " << book.revenue << " ";
    if (book.sale != 0) {
        std::cout << book.revenue / book.sale << std::endl;
    } else {
        std::cout << "(no sale)" << std::endl;
    }

    return 0;
}
