// the elements won't change. needs to be a reference type to access the string
// contents. char& would have worked.

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::getline;

int main() {
    cout << "Please enter a string: ";

    string line;
    getline(cin, line);

    for (char c : line)
        c = 'X';

    cout << "Here is an improved version: \"" << line << "\"" << endl;

    return 0;
}
