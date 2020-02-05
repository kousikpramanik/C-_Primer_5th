#include <vector>
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> ivec;
    for (int input; std::cin >> input;) { ivec.push_back(input); }
    std::sort(ivec.begin(), ivec.end());

    std::list<int> ilst;
    std::unique_copy(ivec.cbegin(), ivec.cend(), std::back_inserter(ilst));
    for (auto n : ilst) { std::cout << n << ' '; }
    std::cout << '\n';

    return 0;
}
