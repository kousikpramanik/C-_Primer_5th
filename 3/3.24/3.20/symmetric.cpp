#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main() {
    vector<int> integers;

    int temp = 0;
    while (cin >> temp)
        integers.push_back(temp);

    // ceiling of (m / 2) = floor of ((m + 1) / 2)
    // use the ceiling instead of floor for mid, because we need to
    // do the task while left != mid, i.e. "0" to "mid - 1"
    for (auto left = integers.cbegin(), right = integers.cend(), mid = left + (right - left + 1) / 2;
         left != mid; ++left) {
        // don't use --right in the loop expression part
        // example: left and right both pointing to the only element
        // of the vector, performing ++left is legal, --right is not.
        --right;

        if (left != right)
            cout << *left + *right << ' ';
        else
            cout << *left;
    }
    cout << endl;

    return 0;
}
