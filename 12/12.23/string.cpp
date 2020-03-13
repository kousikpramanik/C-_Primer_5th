#include <iostream>
#include <string>

int main() {
    std::string s1("this is a test.");
    std::string s2("this is also a test.");

    std::string s12 = s1 + ' ' + s2;
    std::cout << s12 << '\n';

    return 0;
}
