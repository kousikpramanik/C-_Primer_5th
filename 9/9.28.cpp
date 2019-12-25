#include <iostream>
#include <forward_list>
#include <string>

void addStr(std::forward_list<std::string> &lst, const std::string &str1, const std::string &str2) {
    auto prev = lst.before_begin();
    auto curr = lst.begin();
    while (curr != lst.end()) {
        if (*curr == str1) {
            lst.insert_after(prev, str2);
            return;
        }
        prev = curr;
        ++curr;
    }
    if (curr == lst.end()) { // could not find str1 in lst
        lst.insert_after(prev, str2);
        return;
    }
}

int main() {
    std::forward_list<std::string> flst{"This", "is", "a", "test"};
    for (const auto &s : flst) { std::cout << s << ' '; }
    std::cout << '\n';

    addStr(flst, "a", "really");
    for (const auto &s : flst) { std::cout << s << ' '; }
    std::cout << '\n';

    addStr(flst, "hmmmmmm", "idk");
    for (const auto &s : flst) { std::cout << s << ' '; }
    std::cout << '\n';

    return 0;
}
