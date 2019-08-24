#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::getline;

int main()
{
        string s1, s2;

        cout << "Enter the first line." << endl;
        getline(cin, s1);
        cout << "Enter the second line." << endl;
        getline(cin, s2);

        if (s1 == s2)
                cout << "The strings are equal." << endl;
        else if (s1 > s2)
                cout << "\"" << s1 << "\" is larger" << endl;
        else
                cout << "\"" << s2 << "\" is larger" << endl;

        return 0;
}
