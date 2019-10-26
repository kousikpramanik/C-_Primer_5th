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
    Sales_data running;

    double price = 0.0;
    if (cin >> running.ISBN >> running.sale >> price) {
        running.revenue = running.sale * price;
        unsigned count = 1;
        Sales_data curr;
        while (cin >> curr.ISBN >> curr.sale >> price) {
            curr.revenue = curr.sale * price;
            if (running.ISBN == curr.ISBN) {
                ++count;
            } else {
                cout << count << " transaction(s) on ISBN " << running.ISBN << endl;
                running = curr;
                count = 1;
            }
        }
        cout << count << " transaction(s) on ISBN " << running.ISBN << endl;
        return 0;
    } else {
        cerr << "Input is invalid/empty" << endl;
        return -1;
    }
}
