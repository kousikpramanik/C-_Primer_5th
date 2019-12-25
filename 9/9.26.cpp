#include <list>
#include <vector>
#include <iterator>
#include <iostream>

int main() {
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    std::list<int> ilst(std::begin(ia), std::end(ia));
    std::vector<int> ivec(std::begin(ia), std::end(ia));

    for (auto iter = ilst.begin(); iter != ilst.end();) { // compute end each time since iterators get invalidated
        if (*iter % 2) { // odd
            iter = ilst.erase(iter);
        } else {
            ++iter;
        }
    }

    for (auto iter = ivec.begin(); iter != ivec.end();) { // compute end each time since iterators get invalidated
        if (!(*iter % 2)) {
            iter = ivec.erase(iter);
        } else {
            ++iter;
        }
    }

    std::cout << "ia: ";
    for (auto n : ia) { std::cout << n << ' '; }
    std::cout << '\n';

    std::cout << "ilst: ";
    for (auto n : ilst) { std::cout << n << ' '; }
    std::cout << '\n';

    std::cout << "ivec: ";
    for (auto n : ivec) { std::cout << n << ' '; }
    std::cout << '\n';

    return 0;
}
