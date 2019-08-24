// once again, range for is much better.

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::getline;

int main()
{
        cout << "Please enter a string: ";

        string line;
        getline(cin, line);

        decltype(line.size()) i = 0;
        while (i != line.size()) {
                line[i] = 'X';
                ++i;
        }

        cout << "Here is an improved version: \"" << line << "\"" << endl;

        return 0;
}
