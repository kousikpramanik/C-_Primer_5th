#include <iostream>
#include <vector>

using std::cout;
using std::endl;

using std::vector;

int main()
{
        vector<int> v1(10);
        for (decltype(v1.size()) i = 0; i != v1.size(); ++i)
                v1[i] = i;

        vector<int> v2(v1);

        cout << "v1" << endl;
        for (auto n : v1) {
                cout << n << ' ';
        }
        cout << endl;

        cout << "v2" << endl;
        for (auto n : v2) {
                cout << n << ' ';
        }

        return 0;
}
