#include <iostream>
#include <forward_list>

int main() {
    std::forward_list<int> iflst{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Original list: ";
    for (auto n : iflst) { std::cout << n << ' '; };
    std::cout << '\n';

    auto prev = iflst.before_begin();
    auto curr = iflst.begin();
    while (curr != iflst.end()) {
        if (*curr % 2)
            curr = iflst.erase_after(prev);
        else {
            prev = curr;
            ++curr;
        }
    }

    std::cout << "Modified list: ";
    for (auto n : iflst) { std::cout << n << ' '; };
    std::cout << '\n';

    return 0;
}
