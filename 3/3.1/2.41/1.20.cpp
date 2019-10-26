#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;

struct Sales_data {
    string ISBN;
    unsigned sale = 0;
    double revenue = 0.0;
};

int main() {
    Sales_data book;

    double price = 0.0;
    while (cin >> book.ISBN >> book.sale >> price) {
        book.revenue = price * book.sale;
        cout << book.ISBN << " " << book.sale << " " << book.revenue << " " << price << endl;
    }

    return 0;
}
