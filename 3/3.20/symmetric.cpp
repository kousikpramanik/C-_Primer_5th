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

    for (decltype(integers.size()) i = 0, j = integers.size() - 1;
         i <= j; ++i, --j) {
        if (i == j)
            cout << integers[i];
        else
            cout << integers[i] + integers[j] << ' ';
    }
    cout << endl;

    return 0;
}
