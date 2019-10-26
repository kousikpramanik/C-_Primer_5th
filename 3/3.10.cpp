#include <iostream>
#include <string>
#include <cctype>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::getline;

using std::ispunct;

int main() {
    cout << "Enter a string: ";

    string line;
    getline(cin, line);

    cout << "Here is an improved version: ";
    for (auto c : line)
        if (!ispunct(c))
            cout << c;
    cout << endl;

    return 0;
}
