#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::getline;

using std::vector;

using std::toupper;

int main()
{
        vector<string> text;

        string temp;
        while (getline(cin, temp))
                text.push_back(temp);

        for (auto it = text.begin(); it != text.end() && !it->empty(); ++it)
                for (auto str_it = it->begin(); str_it != it->end(); ++str_it)
                        *str_it = toupper(*str_it);

        for (auto it = text.cbegin(); it != text.cend(); ++it)
                cout << *it << endl;

        return 0;
}
