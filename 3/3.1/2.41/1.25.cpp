#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

using std::string;

struct Sales_data {
    string ISBN;
    unsigned sale = 0;
    double revenue = 0.0;
};

int main() {
    Sales_data total; // variable to hold data for the next transaction
    // read the first transaction and ensure that there are data to process
    double price = 0.0;
    if (cin >> total.ISBN >> total.sale >> price) {
        total.revenue = total.sale * price;
        Sales_data trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (cin >> trans.ISBN >> trans.sale >> price) {
            trans.revenue = trans.sale * price;
            // if we're still processing the same book
            if (total.ISBN == trans.ISBN) {
                total.sale += trans.sale; // update the running total
                total.revenue += trans.revenue;
            } else {
                // print results for the previous book
                cout << total.ISBN << " " << total.sale << " " << total.revenue << " ";
                if (total.sale != 0)
                    cout << total.revenue / total.sale << endl;
                else
                    cout << "(no sale)" << endl;
                total = trans;
            }
        }
        cout << total.ISBN << " " << total.sale << " " << total.revenue << " "; // print the last transaction
        if (total.sale != 0)
            cout << total.revenue / total.sale << endl;
        else
            cout << "(no sale)" << endl;

        return 0;
    } else {
        // no input! warn the user
        cerr << "No data?!" << endl;
        return -1; // indicate failure
    }
}
