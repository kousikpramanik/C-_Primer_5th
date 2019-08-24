#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::vector;

int main()
{
        vector<int> vect;

        int temp(0);
        while (cin >> temp)
                vect.push_back(temp);

        for (auto n : vect)
                cout << n << ' ';
        cout << endl;

        return 0;
}
