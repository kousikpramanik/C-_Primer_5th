#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main() {
    vector<int> ten;

    for (unsigned i = 1; i <= 10; ++i) {
        int temp(0);
        cin >> temp;
        ten.push_back(temp);
    }

    for (auto it = ten.begin(); it != ten.end(); ++it)
        *it *= 2;

    for (auto n : ten)
        cout << n << ' ';
    cout << endl;

    return 0;
}
