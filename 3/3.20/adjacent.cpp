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

        for (decltype(integers.size()) i = 0; i < integers.size(); ++i) {
                auto print = integers[i];
                ++i;
                if (i < integers.size())
                        print += integers[i];

                cout << print << ' ';
        }
        cout << endl;

        return 0;
}
