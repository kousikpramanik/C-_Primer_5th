#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;

using std::string;

using std::vector;

using std::toupper;

int main()
{
        vector<string> words;

        string temp;
        while (cin >> temp)
                words.push_back(temp);

        for (auto &s : words)
                for (auto &c : s)
                        c = toupper(c);

        unsigned i = 0;
        for (auto s : words) {
                ++i;
                cout << s << ' ';
                if (i == 8) {
                        cout << endl;
                        i = 0;
                }
        }
        if (i != 0)
                cout << endl;

        return 0;
}
