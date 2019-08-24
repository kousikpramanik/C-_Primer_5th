#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
        int val1, val2;

        cout << "Enter two integers: ";
        cin >> val1 >> val2;
        cout << "Integers from " << val1 << " to " << val2
                        << " inclusive are as follows" << endl;
        while (val2 >= val1) {
                cout << val1 << endl;
                ++val1;
        }

        return 0;
}
