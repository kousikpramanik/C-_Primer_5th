#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main()
{
        vector<int> integers;

        int temp = 0;
        while (cin >> temp)
                integers.push_back(temp);

        for (auto it = integers.cbegin(); it != integers.cend(); ++it) {
                auto print = *it;

                ++it;
                if (it != integers.cend())
                        print += *it;
                else
                        --it;

                cout << print << ' ';
        }
        cout << endl;

        return 0;
}
