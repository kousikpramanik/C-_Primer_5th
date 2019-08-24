// range for is much better

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

        for (decltype(line.size()) i = 0; i != line.size(); ++i)
                line[i] = 'X';

        cout << "Here is an improved version: \"" << line << "\"" << endl;

        return 0;
}
