#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

using std::string;

struct Sales_data {
        string ISBN;
        unsigned sale = 0;
        double revenue = 0.0;
};

int main()
{
        Sales_data book;

        double price = 0.0;
        if (cin >> book.ISBN >> book.sale >> price) {
                book.revenue = book.sale * price;
                Sales_data temp;
                while (cin >> temp.ISBN >> temp.sale >> price) {
                        temp.revenue = temp.sale * price;
                        if (book.ISBN == temp.ISBN) {
                                book.sale += temp.sale;
                                book.revenue += temp.revenue;
                        } else {
                                cerr << "Entries must refer "
                                                "to the same ISBN" << endl;
                                break;
                        }
                }
        }

        cout << book.ISBN << " " << book.sale << " " << book.revenue << " ";
        if (book.sale != 0) {
                cout << book.revenue / book.sale << endl;
        } else {
                cout << "(no sale)" << endl;
        }

        return 0;
}
