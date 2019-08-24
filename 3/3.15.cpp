#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::string;

using std::vector;

int main()
{
        vector<string> vect;

        string temp;
        while (cin >> temp)
                vect.push_back(temp);

        for (auto s : vect)
                cout << s << ' ';
        cout << endl;

        return 0;
}
