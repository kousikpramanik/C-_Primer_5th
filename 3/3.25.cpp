#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main() {
    vector<int> scores(11, 0);

    unsigned grade = 0;
    while (cin >> grade) {
        if (grade <= 100) {
            auto it = scores.begin();
            it += grade / 10;
            ++(*it);
        }
    }

    for (auto n : scores) {
        cout << n << ' ';
    }
    cout << endl;

    return 0;
}
