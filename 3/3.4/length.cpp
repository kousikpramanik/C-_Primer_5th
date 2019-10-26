#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::getline;

int main() {
    string s1, s2;

    cout << "Enter the first line." << endl;
    getline(cin, s1);
    cout << "Enter the second line." << endl;
    getline(cin, s2);

    auto size1 = s1.size();
    auto size2 = s2.size();

    if (size1 == size2)
        cout << "The strings are of same length." << endl;
    else if (size1 > size2)
        cout << "\"" << s1 << "\" is longer" << endl;
    else
        cout << "\"" << s2 << "\" is longer" << endl;

    return 0;
}
