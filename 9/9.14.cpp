#include <iostream>
#include <list>
#include <vector>
#include <string>

int main(int argc, char *argv[]) {
    std::list<char *> lstchr;
    for (int i = 0; i != argc; ++i)
        lstchr.push_back(argv[i]);

    std::vector<std::string> vecstr;
    vecstr.assign(lstchr.cbegin(), lstchr.cend());
    for (const auto &s : vecstr) {
        std::cout << s << '\n';
    }

    return 0;
}
