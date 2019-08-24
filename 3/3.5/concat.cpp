#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;

int main()
{
        string big, temp;

        while (cin >> temp)
                big += temp;

        cout << big << endl;

        return 0;
}
